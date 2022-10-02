

#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED

#include<string>
#include<vector>
#include<list>

class Table
{
public:
  Table(std::string keyColumn, const std::vector<std::string>& columns);
  ~Table();
  bool good() const;
  bool insert(const std::string& recordString);
  void find(std::string key, std::vector<std::vector<std::string>>& records) const;
  int select(std::string query, std::vector<std::vector<std::string>>& records) const;

    // We prevent a Table object from being copied or assigned by
    // making the copy constructor and assignment operator unavailable.
  Table(const Table&) = delete;
  Table& operator=(const Table&) = delete;
private:
    size_t mKeyIndex;
    std::string mKey;
    std::vector<std::string> mColumns;
    std::vector<std::list<std::vector<std::string>>> mTable; //Hash table implementation
    bool mGood;
};

class StringParser
{
  public:
    StringParser(std::string text = "")
    {
        setString(text);
    }

    void setString(std::string text)
    {
        m_text = text;
        m_start = 0;
    }

    bool getNextField(std::string& field);

  private:
    std::string m_text;
    size_t m_start;
};

bool stringToDouble(std::string s, double& d);

bool isOperator(std::string op, std::string comp, std::string target, int& counter, bool isNum); //Performs the query comparison
#endif // TABLE_INCLUDED
