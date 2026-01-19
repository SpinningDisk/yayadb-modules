#include <malloc.h>
#include <sqlite3.h>

int register_app(char* name, char* description, void* version, int vesion_type){
    switch version_type{
        case 0:
            pass
        case 1:
            pass
        case _:
            printf(stderr, "Could not register app: Could not infere type of version (between int and string)\n");
            return 1
    }
 
    sqlite3 *db;
    int return_code;
    return_code = sqlite3_open("apps.sql", &db);

    if(return_code){
        fprintf(stderr, "Coundn't open database \"apps.sql\": %s\n", sqlite3_errmsg(db));
        return 1;
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }
    sqlite3_close(db);
}