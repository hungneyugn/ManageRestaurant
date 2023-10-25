#include "staff.h"
#include "vector"
#include "fstream"
#include "string"
#include "table.h"
#include "algorithm"

Staff::Staff()
{
    listTables.resize(numberOfTable);
    this->currentTable = 0;

    std::fstream r_file("listTable.txt", std::ios::in);

    std::string line_r;
    if (r_file.is_open()) {
        while (std::getline(r_file, line_r)) {

            size_t dashPos = line_r.find("-");
            std::string ordinal_char = line_r.substr(0, dashPos);
            int ordinal = stoi(ordinal_char);

            std::string status_char = line_r.substr(dashPos + 1);
            bool status = stoi(status_char);

            listTables.push_back(Table(ordinal, status));
        }
    }
    r_file.close();

    std::fstream w_file("listTable.txt", std::ios::app);
    if (w_file.is_open()) {
        for (int i = 0; i < listTables.size() ; i++)
        {
            w_file << "\n" << this->listTables[i].getOrdinal() << "-" << this->listTables[i].getStatus();
        }
        w_file.close();
    }

}

