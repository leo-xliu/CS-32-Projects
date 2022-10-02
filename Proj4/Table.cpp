#include "Table.h"
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <cstdlib>

bool stringToDouble(std::string s, double& d)
{
    char* end;
    d = std::strtof(s.c_str(), &end);
    return end == s.c_str() + s.size()  &&  !s.empty();
}

bool StringParser::getNextField(std::string& fieldText)
{
    m_start = m_text.find_first_not_of(" \t\r\n", m_start);
    if (m_start == std::string::npos)
    {
        m_start = m_text.size();
        fieldText = "";
        return false;
    }
    if (m_text[m_start] != '\'')
    {
        size_t end = m_text.find_first_of(" \t\r\n", m_start+1);
        fieldText = m_text.substr(m_start, end-m_start);
        m_start = end;
        return true;
    }
    fieldText = "";
    for (;;)
    {
        m_start++;
        size_t end = m_text.find('\'', m_start);
        fieldText += m_text.substr(m_start, end-m_start);
        m_start = (end != std::string::npos ? end+1 : m_text.size());
        if (m_start == m_text.size()  ||  m_text[m_start] != '\'')
            break;
        fieldText += '\'';
    }
    return true;
}

Table::Table(std::string keyColumn, const std::vector<std::string>& columns)
: mGood(false)
{
    //Valid column and keyColumn checker
    int counter = 0;
    if (columns.size() != 0)
    {
        for (size_t i = 0; i < columns.size(); i++)
        {
            if (columns[i] == "")
            {
                counter = 0;
                break;
            }
            if (columns[i] == keyColumn)
            {
                mKeyIndex = i;
                counter++;
            }
            for (size_t j = i + 1; j < columns.size(); j++)
            {
                //Checks for identical strings
                if (columns[i] == columns[j])
                {
                    counter = 0;
                    break;
                }
            }
        }
    }
    if (counter == 1)
    {
        mKey = keyColumn;
        mColumns = columns;
        mTable.resize(1000);
        mGood = true;
    }
}

Table::~Table()
{
}

bool Table::good() const
{
    return(mGood);
}

bool Table::insert(const std::string& recordString)
{
    if (!mGood)
    {
        return false;
    }
    StringParser parse(recordString);
    std::string s;
    std::vector<std::string> temp;
    //Find all strings separated by delimiters
    while (parse.getNextField(s))
    {
        temp.push_back(s);
    }
    if (temp.size() != mColumns.size())
    {
        return false;
    }
    //Find hash key
    unsigned int h = std::hash<std::string>()(temp[mKeyIndex]) % 1000;
    //Insert into hash table using vector copy constructor
    mTable[h].push_back(temp);
    return true;
}

void Table::find(std::string key, std::vector<std::vector<std::string>>& records) const
{
    if (!mGood)
    {
        return;
    }
    records.clear();
    //Find hash key
    unsigned int h = std::hash<std::string>()(key) % 1000;
    std::list<std::vector<std::string>>::const_iterator p = mTable[h].begin();
    //Use iterator to insert all collisions
    for (; p != mTable[h].end(); p++)
    {
        records.push_back(*p);
    }
}

int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const
{
    if (!mGood)
    {
        return -1;
    }
    std::string temp;
    std::vector<std::string> que;
    StringParser parse(query);
    while(parse.getNextField(temp)) //Parse the string into a vector
    {
        que.push_back(temp);
    }
    records.clear();
    if (que.size() != 3) //Check for correct query requirements
    {
        return -1;
    }
    if (std::find(mColumns.begin(), mColumns.end(), que[0]) == mColumns.end()) //Check to make sure the column exists
    {
        return -1;
    }
    int isNum = false; //Determine what type of query it is
    //Check if it is a valid operator
    if (!(que[1] == "<" || que[1] == "<=" || que[1] == ">" || que[1] == ">=" || que[1] == "==" || que[1] == "!=" || que[1] == "=" || que[1] == "LT" || que[1] == "lT" || que[1] == "Lt" || que[1] == "lt" || que[1] == "LE" || que[1] == "Le" || que[1] == "lE" || que[1] == "le" || que[1] == "GT" || que[1] == "Gt" || que[1] == "gT" || que[1] == "gt" || que[1] == "GE" || que[1] == "Ge" || que[1] == "gE" || que[1] == "ge" || que[1] == "NE" || que[1] == "Ne" || que[1] == "nE" || que[1] == "ne" || que[1] == "EQ" || que[1] == "Eq" || que[1] == "eQ" || que[1] == "eq"))
    {
        return -1;
    }
    if (!(que[1] == "<" || que[1] == "<=" || que[1] == ">" || que[1] == ">=" || que[1] == "==" || que[1] == "!=" || que[1] == "="))
    {
        double d;
        if (!stringToDouble(que[2], d)) //If it cannot be converted to double return
        {
            return -1;
        }
        isNum = true;
    }
    size_t index = 0;
    for (; index < mColumns.size(); index++) //Find the target column
    {
        if (que[0] == mColumns[index])
        {
            break;
        }
    }
    int counter = 0; //return value that will count number of fields that are not in proper form
    for (int i = 0; i < mTable.size(); i++) //Iterate through table
    {
        if (mTable[i].size() == 0)
        {
            continue;
        }
        for (std::list<std::vector<std::string>>::const_iterator p = mTable[i].begin(); p != mTable[i].end(); p++) //Iterate through list
        {
            if (isOperator(que[1], que[2], (*p)[index], counter, isNum)) //use helper function to check if operation is satisfied
            {
                records.push_back(*p);
            }
        }
    }
    return counter;
}

bool isOperator(std::string op, std::string comp, std::string target, int& counter, bool isNum)
{
    double cNum = 0;
    double num = 0;
    if (isNum)
    {
        if(!stringToDouble(target, num)) //Convert to double if necesary
        {
            counter++;
            return false;
        }
        stringToDouble(comp, cNum);
    }
    //Comparisons for all operations
    if (op == "<" || op == "LT" || op == "Lt" || op == "lT" || op == "lt")
    {
        if (isNum)
        {
            return(num < cNum);
        }
        else
        {
            return(target < comp);
        }
    }
    else if (op == "<=" || op == "LE" || op == "Le" || op == "lE" || op == "le")
    {
        if (isNum)
        {
            return(num <= cNum);
        }
        else
        {
            return(target <= comp);
        }
    }
    else if (op == ">" || op == "GT" || op == "Gt" || op == "gT" || op == "gt")
    {
        if (isNum)
        {
            return(num > cNum);
        }
        else
        {
            return(target > comp);
        }
    }
    else if (op == ">=" || op == "GE" || op == "Ge" || op == "gE" || op == "ge")
    {
        if (isNum)
        {
            return(num >= cNum);
        }
        else
        {
            return(target >= comp);
        }
    }
    else if (op == "!=" || op == "NE" || op == "Ne" || op == "nE" || op == "ne")
    {
        if (isNum)
        {
            return(num != cNum);
        }
        else
        {
            return(target != comp);
        }
    }
    else
    {
        if (isNum)
        {
            return(num == cNum);
        }
        else
        {
            return(target == comp);
        }
    }
}
