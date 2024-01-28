#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <map>


class SqlSelectQueryBuilder
{

public:
    explicit SqlSelectQueryBuilder() = default;


    std::string buildQuery() {
        if (from.length() == 0)
            return "*";
        return "SELECT " + column + " FROM " + from + " WHERE " + where + ";";
    }


    SqlSelectQueryBuilder& addColumn(const std::string& column) {
        if (this->column.length() > 0)
            this->column += ", ";
        this->column += column;
        return *this;
    }


    SqlSelectQueryBuilder& addColumns(const std::vector<std::string>& columns) {

        for (auto column : columns) {
            if (this->column.length() > 0)
                this->column += ", ";
            this->column += column;
        }
        return *this;
    }


    SqlSelectQueryBuilder& addWhere(const std::string& column, const std::string& value) {
        if (this->where.length() > 0)
            this->where += " AND ";
        this->where += column + "=" + value;
        return *this;
    }


    SqlSelectQueryBuilder& addWhere(const std::map<std::string, std::string>& kv) {

        for (auto& [column, value] : kv) {
            if (this->where.length() > 0)
                this->where += " AND ";
            this->where += column + "=" + value;
        }
        return *this;
    }


    SqlSelectQueryBuilder& addFrom(std::string from) {
        this->from = from;
        return *this;
    }


private:
    std::string from = "";
    std::string where = "";
    std::string column = "";
};




int main()
{

    // Задание 1 (нерасширенный класс)
    {
        SqlSelectQueryBuilder query_builder;
        query_builder.addFrom("students");
        query_builder.addColumn("name").addColumn("phone");
        query_builder.addWhere("id", "42").addWhere("name", "John");

        assert(query_builder.buildQuery() == "SELECT name, phone FROM students WHERE id=42 AND name=John;"
               && "QUERY BUILDER TEST FAILED" );
        std::cout << "Test 1 passed" << std::endl;
    }

    // Задание 2 (расширенный класс)
    {
        SqlSelectQueryBuilder query_builder;
        query_builder.addFrom("students");
        query_builder.addColumns({"name", "phone"});
        query_builder.addWhere( { {"id", "42"}, {"name", "John"} } );

        assert(query_builder.buildQuery() == "SELECT name, phone FROM students WHERE id=42 AND name=John;"
               && "QUERY BUILDER TEST FAILED" );
        std::cout << "Test 2 passed" << std::endl;
    }

    return 0;
}
