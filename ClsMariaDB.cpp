//------------------------------------------------------------------------------
//
// Project:		-
// Target:		LIB
// Filename:	ClsMariaDB.cpp
// Version:		1.0
// History:		Date		By		Content
//				----------	------	--------------------------------------------
//				
// 
//------------------------------------------------------------------------------
// Include
//------------------------------------------------------------------------------
#pragma	hdrstop
#include "ClsMariaDB.h"
//------------------------------------------------------------------------------
// ClsMariaDB
//------------------------------------------------------------------------------
ClsMariaDB::ClsMariaDB(void)
{

}
//------------------------------------------------------------------------------
ClsMariaDB::ClsMariaDB(Connection_details desc)
{
    Init(desc);
}
//------------------------------------------------------------------------------
// ~ClsMariaDB
//------------------------------------------------------------------------------
ClsMariaDB::~ClsMariaDB(void)
{
    if(state != DB_STATE::disconnected)
    {
        Disconnect();        
    }
    state = DB_STATE::disconnected;
}
//------------------------------------------------------------------------------
// Init
//------------------------------------------------------------------------------
void ClsMariaDB::Init(Connection_details desc)
{
    //------------------------------
    // Set database server info.
    //------------------------------
    memset(&m_desc, 0, sizeof(Connection_details));
    m_desc.server = desc.server;
    m_desc.database = desc.database;
    m_desc.user = desc.user;
    m_desc.password = desc.password;

    state = DB_STATE::disconnected;
}
//------------------------------------------------------------------------------
// SetDatabaseInfo
//------------------------------------------------------------------------------
void ClsMariaDB::SetDatabaseInfo(Connection_details desc)
{
    Init(desc);
}
//------------------------------------------------------------------------------
// Connect
//------------------------------------------------------------------------------
bool ClsMariaDB::Connect(void)
{
    if(state == DB_STATE::disconnected)
    {
        conn = mysql_init(NULL);
        if(!mysql_real_connect(conn, m_desc.server.c_str(), m_desc.user.c_str(), m_desc.password.c_str(), m_desc.database.c_str(), 0, NULL, 0)) {
    
            printf("Connection error : %s\n", mysql_error(conn));
            return (false);
        }
    }
    state = DB_STATE::connected;
    return (true);
}
//------------------------------------------------------------------------------
// Disconnect
//------------------------------------------------------------------------------
void ClsMariaDB::Disconnect(void)
{
    mysql_close(conn);
    state = DB_STATE::disconnected;
}
//------------------------------------------------------------------------------
// ExecuteQuery
//------------------------------------------------------------------------------
MYSQL_RES* ClsMariaDB::ExecuteQuery(string qry)
{
    if(state != DB_STATE::connected || conn == NULL)
    {
        return NULL;
    }

    //if(mysql_query(conn, qry.c_str())) { 
    if(mysql_real_query(conn, qry.c_str(), qry.length())) { 
        
        printf("MYSQL query error : %s\n", mysql_error(conn));
        return NULL;
    }

    return mysql_use_result(conn);
}
//------------------------------------------------------------------------------
// Execute
//------------------------------------------------------------------------------
int ClsMariaDB::Execute(string qry)
{
    /*---------------------------
    update, delete 쿼리 실행 함수
    ---------------------------*/
    if(state != DB_STATE::connected || conn == NULL)
    {
        return false;
    }

    //if(mysql_query(conn, qry.c_str())) { 
    if(mysql_real_query(conn, qry.c_str(), qry.length())) { 
        
        printf("MYSQL query error : %s\n", mysql_error(conn));
        return false;
    }

    int ret = 0;
    ret = mysql_affected_rows(conn);        // 변환 한 행의 수를 반환
    return (ret);
}
//------------------------------------------------------------------------------
//  GetDatabaseState
//------------------------------------------------------------------------------
DB_STATE ClsMariaDB::GetDatabaseState(void)
{
    return (state);
}
//------------------------------------------------------------------------------
// End of ClsMariaDb.cpp
//------------------------------------------------------------------------------