//------------------------------------------------------------------------------
//
// Project:		
// Target:		
// Filename:	mariadbTest2.cpp
// Version:		1.0
// History:		Date		By		Content
//				----------	------	--------------------------------------------
//				
// 
//------------------------------------------------------------------------------
// Include
//------------------------------------------------------------------------------
#include "ClsMariaDB.h"
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
int main(void)
{
    MYSQL_RES* res;
    MYSQL_ROW row;  // MYSQL_ROW type : char ** type
    string qry="";

    Connection_details DBdesc;
    DBdesc.server = "localhost";
    DBdesc.user = "gildong";
    DBdesc.password = "gildong";
    DBdesc.database = "ygd";
    
    ClsMariaDB MDB(DBdesc);

    if(!MDB.Connect())
    {
        printf("DB connect fail");
        exit(1);
    }

    DB_STATE state = MDB.GetDatabaseState();
    printf("[%d]", (int)state);
    switch(state)
    {
    case DB_STATE::connected:
        printf("db connected!");
        break;
    case DB_STATE::disconnected:
        printf("db disconnected!");        
        break;
    }

    //------------------------------------------------------------------
    // select query
    //------------------------------------------------------------------
    printf("----------------------------------------------\n");
    printf("select\n");
    printf("----------------------------------------------\n");
    qry = "select * from GWTEST";
    res = MDB.ExecuteQuery(qry);
    if(res == NULL)
    {
        printf("ExecuteQuery fail");
        exit(1);
    }

    printf("query result : \n");
    while((row = mysql_fetch_row(res)) != NULL)
    {     
        printf("%s \t %s \t %s\n", row[0], row[1], row[4]);
    }
    printf("sel query end\n");
    mysql_free_result(res);


    //------------------------------------------------------------------
    // update query
    //------------------------------------------------------------------
    printf("----------------------------------------------\n");
    printf("update\n");
    printf("----------------------------------------------\n");
    qry = "UPDATE ygd.GWTEST SET INSTALL_POSITION = 90 where GW_ID=1";    
    int ret = 0;
    if((ret = MDB.Execute(qry)) < 0)
    {
        printf("ExecuteQuery fail\n");
        exit(1);
    }
    printf("upd query end [%d]\n", ret);
    //mysql_free_result(res);

    //------------------------------------------------------------------
    // select query
    //------------------------------------------------------------------
    printf("----------------------------------------------\n");
    printf("select\n");
    printf("----------------------------------------------\n");
    qry = "select * from GWTEST";
    res = MDB.ExecuteQuery(qry);
    if(res == NULL)
    {
        printf("ExecuteQuery fail");
        exit(1);
    }

    printf("query result : \n");
    while((row = mysql_fetch_row(res)) != NULL)
    {     
        printf("%s \t %s \t %s\n", row[0], row[1], row[4]);
    }
    printf("sel query end\n");
    mysql_free_result(res);

    MDB.Disconnect();

    return (0);
}
