# LSQL IS STILL WORK IN PROGRESS SO IF YOU ENCOUNTER ANY BUGS THEYRE GONNA BE FIXED IN OFFICIAL RELEASE 

# LSQL – Lightweight Single-File Database CLI

LSQL is a minimal, single-file, command-line database management tool written in C. It allows you to create databases, manage users, and list databases and users—all from a simple terminal interface. Perfect for learning or experimenting with database concepts in C.  

## Features

- **Create databases** (`CREATE_DB <dbname>`)
- **Add users** (`CREATE_USR <username>`) to the current database
- **List users** in the current database (`LIST_USR`)
- **List all databases** in the current directory (`LIST_DB`)
- **Switch between databases** (`USE <dbname>`)
- **Exit the CLI** (`\q`)

## Usage

1. **Compile the program**

    gcc -o lsql lsql.c

2. **Run LSQL**

    ./lsql

3. **Commands**

| Command | Description |
|---------|-------------|
| CREATE_DB <dbname> | Creates a new database file `<dbname>.db` |
| USE <dbname> | Switch to an existing database |
| CREATE_USR <username> | Add a user to the current database |
| LIST_USR | List all users in the current database |
| LIST_DB | List all `.db` files in the current directory |
| \q | Exit LSQL |

### Example Session

    LSQL[]> CREATE_DB testdb
    created db: testdb
    LSQL[testdb]> CREATE_USR alice
    User: alice Written to DB: testdb
    LSQL[testdb]> CREATE_USR bob
    User: bob Written to DB: testdb
    LSQL[testdb]> LIST_USR
    Users:
    alice
    bob
    LSQL[testdb]> LIST_DB
    DB List:
    testdb.db
    LSQL[testdb]> \q

## Implementation Details

- Databases are stored as plain text files with a `.db` extension.
- Users are saved in the format `user: <username>` inside the database file.
- The CLI uses a simple dispatcher function to parse commands.
- No external dependencies, fully contained in a single C file.

## Limitations

- Only supports basic user storage; no advanced SQL features.
- Database files are plain text; no encryption or indexing.
- Command parsing is strict; input must match the exact syntax.

## Future Improvements

- Add deletion of users and databases
- Implement simple authentication
- Enhance command parsing with more SQL-like syntax
- Support for multiple tables per database
