#include "query_funcs.h"

// return number of tuples in "tableName"
int countNum(connection *C, string tableName) {
	pqxx::work w(*C);
	pqxx::result r = w.exec("SELECT COUNT(*) FROM \"" + tableName + "\";");
	w.commit();
	return r[0][0].as<int>();
}

void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
  //	int playerID = countNum(C, "PLAYER") + 1;
	pqxx::work w(*C);
	// where is player id ?
	pqxx::result r = w.exec("INSERT INTO \"PLAYER\" (\"TEAM_ID\", \"UNIFORM_NUM\", \"FIRST_NAME\", \"LAST_NAME\", \"MPG\", \"PPG\", \"RPG\", \"APG\", \"SPG\", \"BPG\") VALUES("
	                        + to_string(team_id) + ","
	                        + to_string(jersey_num) + ",'" + first_name + "','" + last_name + "',"
	                        + to_string(mpg) + "," + to_string(ppg) + "," + to_string(rpg) + ","
	                        + to_string(apg) + "," + to_string(spg) + "," + to_string(bpg) + ");");
	w.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
  //	int teamID = countNum(C, "TEAM") + 1;
	pqxx::work w(*C);
	pqxx::result r = w.exec("INSERT INTO \"TEAM\" (\"NAME\", \"STATE_ID\", \"COLOR_ID\", \"WINS\", \"LOSSES\") VALUES('"
	                        + name + "'," + to_string(state_id) + "," + to_string(color_id) + ","
	                        + to_string(wins) + "," + to_string(losses) + ");");
	w.commit();
}


void add_state(connection *C, string name)
{
  //	int stateID = countNum(C, "STATE") + 1;
	pqxx::work w(*C);
	pqxx::result r = w.exec("INSERT INTO \"STATE\" (\"NAME\") VALUES('"
	                        + name + "');");
	w.commit();
}


void add_color(connection *C, string name)
{
  //	int colorID = countNum(C, "COLOR") + 1;
	pqxx::work w(*C);
	pqxx::result r = w.exec("INSERT INTO \"COLOR\" (\"NAME\") VALUES('"
	                        + name + "');");
	w.commit();
}


void query1(connection *C,
            int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
           )
{
	string cmd;
	if (use_mpg == 0 && use_ppg == 0 && use_rpg == 0 && use_apg == 0 && use_spg == 0 && use_bpg == 0) {
		cmd = "SELECT * FROM \"PLAYER\"";
	}
	else {
		cmd = "SELECT * FROM \"PLAYER\" WHERE";
		cmd = use_mpg == 1 ? cmd + " \"MPG\">=" + to_string(min_mpg) + " AND \"MPG\" <=" + to_string(max_mpg) + " AND" : cmd;
		cmd = use_ppg == 1 ? cmd + " \"PPG\">=" + to_string(min_ppg) + " AND \"PPG\" <=" + to_string(max_ppg) + " AND" : cmd;
		cmd = use_rpg == 1 ? cmd + " \"RPG\">=" + to_string(min_rpg) + " AND \"RPG\" <=" + to_string(max_rpg) + " AND" : cmd;
		cmd = use_apg == 1 ? cmd + " \"APG\">=" + to_string(min_apg) + " AND \"APG\" <=" + to_string(max_apg) + " AND" : cmd;
		cmd = use_spg == 1 ? cmd + " \"SPG\">=" + to_string(min_spg) + " AND \"SPG\" <=" + to_string(max_spg) + " AND" : cmd;
		cmd = use_bpg == 1 ? cmd + " \"BPG\">=" + to_string(min_bpg) + " AND \"BPG\" <=" + to_string(max_bpg) + " AND" : cmd;
		if(cmd[cmd.size()-1 == 'D']) {
			cmd = cmd.substr(0, cmd.size() - 4);
		}
		cmd += ";";
	}

	cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
	pqxx::work w(*C);
	pqxx::result r = w.exec(cmd.c_str());
	w.commit();
	for(int i = 0; i < r.size(); i++) {
		for(int j = 0; j < 11; j++) {
			cout << r[i][j].as<string>();
			if(j != 10) {cout << " ";}
		}
		cout << endl;
	}
}


void query2(connection *C, string team_color)
{
	string cmd = "SELECT \"TEAM\".\"NAME\" FROM \"TEAM\", \"COLOR\" WHERE \"TEAM\".\"COLOR_ID\"=\"COLOR\".\"COLOR_ID\" AND \"COLOR\".\"NAME\"='" + team_color + "';";
	pqxx::work w(*C);
	pqxx::result r = w.exec(cmd.c_str());
	w.commit();
	cout << "NAME" << endl;
	for(int i = 0; i < r.size(); i++) {
		cout << r[i][0] << endl;
	}
}


void query3(connection *C, string team_name)
{
	string cmd = "SELECT \"PLAYER\".\"FIRST_NAME\", \"PLAYER\".\"LAST_NAME\" FROM \"PLAYER\", \"TEAM\" WHERE \"PLAYER\".\"TEAM_ID\"=\"TEAM\".\"TEAM_ID\" AND \"TEAM\".\"NAME\"='" + team_name + "' ORDER BY \"PLAYER\".\"PPG\" DESC;";
	pqxx::work w(*C);
	pqxx::result r = w.exec(cmd.c_str());
	w.commit();
	cout << "FIRST_NAME LAST_NAME" << endl;
	for(int i = 0; i < r.size(); i++) {
		cout << r[i][0] << " " << r[i][1] << endl;
	}
}


void query4(connection *C, string team_state, string team_color)
{
	string cmd = "SELECT \"FIRST_NAME\", \"LAST_NAME\", \"UNIFORM_NUM\" FROM \"PLAYER\", \"TEAM\", \"STATE\", \"COLOR\" WHERE \"PLAYER\".\"TEAM_ID\"=\"TEAM\".\"TEAM_ID\" AND \"TEAM\".\"STATE_ID\"=\"STATE\".\"STATE_ID\" AND \"TEAM\".\"COLOR_ID\"=\"COLOR\".\"COLOR_ID\" AND \"STATE\".\"NAME\"='" + team_state + "' AND \"COLOR\".\"NAME\"='" + team_color + "';";
	pqxx::work w(*C);
	pqxx::result r = w.exec(cmd.c_str());
	w.commit();
	cout << "FIRST_NAME LAST_NAME UNIFORM_NUM" << endl;
	for(int i = 0; i < r.size(); i++) {
		cout << r[i][0] << " " << r[i][1] << " " << r[i][2] << endl;
	}
}


void query5(connection *C, int num_wins)
{
	string cmd = "SELECT \"FIRST_NAME\", \"LAST_NAME\", \"TEAM\".\"NAME\", \"TEAM\".\"WINS\" FROM \"PLAYER\", \"TEAM\" WHERE \"PLAYER\".\"TEAM_ID\"=\"TEAM\".\"TEAM_ID\" AND \"TEAM\".\"WINS\" > " + to_string(num_wins) + ";";
	pqxx::work w(*C);
	pqxx::result r = w.exec(cmd.c_str());
	w.commit();
	cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
	for(int i = 0; i < r.size(); i++) {
		cout << r[i][0] << " " << r[i][1] << " " << r[i][2] << " " << r[i][3] << endl;
	}
}







