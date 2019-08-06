//------------------------------------------------------------------------------
//
// Project:		-
// Target:		LIB
// Filename:	ClsMariaDB.h
// Version:		1.0
// History:		Date		By		Content
//				----------	------	--------------------------------------------
//				
// 
//------------------------------------------------------------------------------
#ifndef	ClsMARIADBH
#define	ClsMARIADBH
//------------------------------------------------------------------------------
// Include
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory.h>
#include <mysql.h>
//------------------------------------------------------------------------------
// name space
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
// Typedef Definition
//------------------------------------------------------------------------------
enum class DB_STATE
{
    disconnected = 0,
    connected = 1,
    connecting = 2
};
//------------------------------------------------------------------------------
typedef struct{
 
    string server;       // host address ("remote ip" or "localhost")
    string user;         // user id
    string password;     // user password
    string database;     // database name
}Connection_details;
//------------------------------------------------------------------------------
// class
//------------------------------------------------------------------------------
class ClsMariaDB
{
private:
    MYSQL *conn;
    Connection_details m_desc;    
    DB_STATE  state;

    void Init(Connection_details desc);
public:    

    ClsMariaDB(void);
    ClsMariaDB(Connection_details desc);
    ~ClsMariaDB(void);

    void SetDatabaseInfo(Connection_details desc);
    bool Connect(void);
    void Disconnect(void);
    MYSQL_RES* ExecuteQuery(string qry);    // MYSQL_RES is null if then error.
    int Execute(string qry);               // update, delete실행
    DB_STATE GetDatabaseState(void);
};
//------------------------------------------------------------------------------
#endif  // ClsMARIADBH
//------------------------------------------------------------------------------
// End of ClsMariaDB.h
//------------------------------------------------------------------------------