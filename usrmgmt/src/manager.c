#include <malloc.h>
#include <sqlite3.h>

typedef struct s_AppData{
    void* version;
    char name[];
}t_AppData;

int check_status(void* ret, int argc, char **argv, char **column){
    printf("[CHECKSTATUS]\tentring loop");
    int *allocated_index = (int*)malloc(sizeof(int));
    *allocated_index = argc;
    ret = (void*)allocated_index;
    for(int i=0; i<argc; i++){
        printf("[CHECKSTATUS]\t\t%d:%s/%s\n", i, argv[i], column[i]);
    }
    return 0;
}
int checkup_app(){
    printf("[CHECKUP]\tEntering app checkup:\n");
    sqlite3 *db = NULL;
    int ret = sqlite3_open("Apps.sql", &db);
    if(ret!=0){
        fprintf(stderr, "[CHECKUP]\t\t[FE]could not open Apps.sql:\n%s", sqlite3_errmsg(db));
        return 1;
    }else{
        printf("[CHECKUP]\t\tApps database found\n");
    }
    char** tableExistsError;
    void* tableExistsRet;
    int tableExists = sqlite3_exec(db, "SELECT COUNT(TYPE) FROM sqlite_master WHERE TYPEW='table' AND name='APPS';", check_status, tableExistsRet, tableExistsError);
    printf(":3\n");
    if(*(int*)(tableExistsRet)){
        fprintf(stderr, "[CHECKUP]\t\tApps database does not appear to contain Apps table\n");
        sqlite3_exec(db, "CREATE TABLE main.APPS (ID INTEGER PRIMARY KEY, name TEXT NOT NULL, description TEXT, version TEXT NOT NULL)", NULL, NULL, tableExistsError);
        printf("[CHECKUP]\t\tApps table has been created\n");
        printf("[CHECKUP]\t\trestarting...\n");
        return checkup_app();
    }
    printf("%d:3\n", tableExists);

    sqlite3_close(db);
    return 0;
}
int register_app(char* name, char* description, void* version, int versionType){
    switch(versionType){
        case 0:
            break;
        case 1:
            break;
        default:
            fprintf(stderr, "Could not register app: Could not infere type of version (between int and string)\n");
            return 1;
    }
 
    sqlite3 *db;
    int ret;
    ret = sqlite3_open("apps.sql", &db);

    if(ret){
        fprintf(stderr, "Coundn't open database \"apps.sql\": %s\n", sqlite3_errmsg(db));
        return 1;
    }else{
        fprintf(stderr, "Opened database successfully\n");
        return 2;
    }
    sqlite3_close(db);
    return 0;
}

int main(){
    checkup_app();
    return 0;
}