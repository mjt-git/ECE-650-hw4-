#include <iostream>
#include <fstream>
#include <pqxx/pqxx>
#include <string.h>
#include <string>
#include <vector>
#include "exerciser.h"
#include "query_funcs.h"

#define PLAYER "PLAYER"
#define TEAM "TEAM"
#define STATE "STATE"
#define COLOR "COLOR"

using namespace std;
using namespace pqxx;

bool isTableExist(string tableName, pqxx::connection * c) {
  pqxx::work w(*c);
  pqxx::result r = w.exec("select count(*) from pg_class where relname = '" + tableName + "';");
  w.commit();
  if (r[0][0].as<int>() > 0) {
    return true;
  }
  return false;
}

void dropExistedTable(vector<string> vec, pqxx::connection * c) {
  for (string table : vec) {
    if (isTableExist(table, c)) {
      pqxx::work w(*c);
      pqxx::result r = w.exec("DROP TABLE \"" + table + "\";");
      w.commit();
    }
  }
}

void createTable(pqxx::connection * c, string cmd) {
  pqxx::work w(*c);
  pqxx::result r = w.exec(cmd.c_str());
  w.commit();
}

void createAllTables(pqxx::connection * c) {
  vector<string> createCmds;

  string cmdPly = string("CREATE TABLE \"PLAYER\"(\"PLAYER_ID\" SERIAL NOT NULL, \"TEAM_ID\" INT NOT NULL, ") +
    "\"UNIFORM_NUM\" INT NOT NULL, \"FIRST_NAME\" VARCHAR(50) NOT NULL, \"LAST_NAME\" VARCHAR(50) NOT NULL, " +
    "\"MPG\" INT NOT NULL, \"PPG\" INT NOT NULL, \"RPG\" INT NOT NULL, " +
    "\"APG\" INT NOT NULL, \"SPG\" DECIMAL(10,1) NOT NULL, \"BPG\" DECIMAL(10,1) NOT NULL, " +
    "PRIMARY KEY (\"PLAYER_ID\"), FOREIGN KEY (\"TEAM_ID\") REFERENCES \"TEAM\"(\"TEAM_ID\") ON UPDATE CASCADE);";

  string cmdTeam = string("CREATE TABLE \"TEAM\"(\"TEAM_ID\" SERIAL NOT NULL, \"NAME\" VARCHAR(50) NOT NULL, ") +
                    "\"STATE_ID\" INT NOT NULL, \"COLOR_ID\" INT NOT NULL, \"WINS\" INT NOT NULL, \"LOSSES\" " +
                    "INT NOT NULL, PRIMARY KEY (\"TEAM_ID\"), FOREIGN KEY (\"STATE_ID\") REFERENCES \"STATE\"(\"STATE_ID\") ON UPDATE CASCADE, FOREIGN KEY (\"COLOR_ID\") REFERENCES \"COLOR\"(\"COLOR_ID\") ON UPDATE CASCADE);";


  string cmdState = "CREATE TABLE \"STATE\"(\"STATE_ID\" SERIAL NOT NULL, \"NAME\" VARCHAR(50) NOT NULL, PRIMARY KEY (\"STATE_ID\"));";


  string cmdColor = "CREATE TABLE \"COLOR\"(\"COLOR_ID\" SERIAL NOT NULL, \"NAME\" VARCHAR(50) NOT NULL, PRIMARY KEY (\"COLOR_ID\"));";

  createCmds.push_back(cmdColor);
  createCmds.push_back(cmdState);
  createCmds.push_back(cmdTeam);
  createCmds.push_back(cmdPly);
  for(string cmd : createCmds) {
    createTable(c, cmd);
  }
}

void insertApos(string & str) {   // add ' to string if content contains '
  size_t pos = -1;
  size_t aposIdx;
  while((aposIdx = str.find("'", pos + 1)) != string::npos) {
    str.insert(aposIdx, "'");
    pos = aposIdx + 2;
  }
}

void parseLine(vector<vector<string> > & v, string tmpLine) {
  vector<string> res;
  size_t pos = -1;
  while(true) {
    size_t nextBlkIdx = tmpLine.find(" ", pos + 1);
    if(nextBlkIdx == string::npos) {
      string tmpStr = tmpLine.substr(pos + 1, tmpLine.size() - (pos + 1));
      insertApos(tmpStr);
      res.push_back(tmpStr);
      break;
    }
    string tmpStr = tmpLine.substr(pos + 1, nextBlkIdx - (pos + 1));
    insertApos(tmpStr);
    res.push_back(tmpStr);
    pos = nextBlkIdx;
  }
  v.push_back(res);
}

vector<vector<string> > parseTableTxt(string filePath) {
  ifstream file(filePath.c_str());
  vector<vector<string> > res;
  string tmpLine;
  while(getline(file, tmpLine)) {
    parseLine(res, tmpLine);
  }
  return res;
}

void insertPlayerTable(pqxx::connection * c) {
  vector<vector<string> > txt = parseTableTxt("./player.txt");
  for(int i = 0; i < txt.size(); i++){
    add_player(c, stoi(txt[i][1]), stoi(txt[i][2]), txt[i][3], txt[i][4], 
      stoi(txt[i][5]), stoi(txt[i][6]), stoi(txt[i][7]), stoi(txt[i][8]), 
      stod(txt[i][9]), stod(txt[i][10]));
  }
}

void insertTeamTable(pqxx::connection * c) {
  vector<vector<string> > txt = parseTableTxt("./team.txt");
  for(int i = 0; i < txt.size(); i++){
    add_team(c, txt[i][1], stoi(txt[i][2]), stoi(txt[i][3]), stoi(txt[i][4]), stoi(txt[i][5]));
  }
}

void insertStateTable(pqxx::connection * c) {
  vector<vector<string> > txt = parseTableTxt("./state.txt");
  for(int i = 0; i < txt.size(); i++){
    add_state(c, txt[i][1]);
  }
}

void insertColorTable(pqxx::connection * c) {
  vector<vector<string> > txt = parseTableTxt("./color.txt");
  for(int i = 0; i < txt.size(); i++){
    add_color(c, txt[i][1]);
  }
}

void insertAllTables(pqxx::connection * c) {
  insertColorTable(c);
  insertStateTable(c);
  insertTeamTable(c);
  insertPlayerTable(c);

}


int main (int argc, char *argv[])
{

  //Allocate & initialize a Postgres connection object
  connection *C = NULL;

  try {
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
  string tablesArr[4] = {PLAYER, TEAM, STATE, COLOR};
  vector<string> tables(tablesArr, tablesArr + 4);
  dropExistedTable(tables, C);   // if any table exists, drop it

  createAllTables(C);
  insertAllTables(C);

  exercise(C);

  
  //Close database connection
  C->disconnect();
  if(C != NULL) {delete C;}

  return 0;
  }     

/*
int main() {
  vector<vector<string> > res;
  res = parseTableTxt("./player.txt");
  //  string tmpLine = "3 1 25 Jordan Chatman 25 9 2 1 0.6 0.2";
  //  parseLine(res, tmpLine);
  for(int i = 0; i < res[0].size(); i++) {
    cout << i << "th column: " << res[0][i] << endl;
  }
  return 0;
  } */  


