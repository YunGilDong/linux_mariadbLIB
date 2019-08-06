#
# Environment
#
MARIADB_INC = /usr/include/mysql
MARIADB_LIB = /usr/lib64/mysql 

CCOPTS = -c -I$(MARIADB_INC)
LDOPTS = -L$(MARIADB_LIB)

CC = g++ $(CCOPTS)
LINK = g++ $(LDOPTS)
.cpp.o:	; $(CC) $<
LIBS = -lmysqlclient

OBJS = mariadbTest2.o ClsMariaDB.o

TARGET = mariadbTest2

default:	$(TARGET)

$(TARGET):	$(OBJS)
	$(LINK) $(OBJS) -o $@ $(LIBS)