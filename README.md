# Library 📚

Documentation for the **"Library"** Information System<br>
This project is a developed information system for a library, containing information about a specific set of books, including their ratings, title, author, keywords, genre, and publication date.     
The system requires a file to store and read changes made. Without such a file, work with the system cannot continue.    
There are two types of users in the system – clients and admins.<br>

**Each type of user has the right to:**

1. Display information about all books.
2. Search for information about a selected book (by ID number).
3. Search for a book by keyword, title, or author.
4. Sort books by title, author, publication year, or rating, both in ascending and descending order.
5. Open a file.
6. Close a file.
7. Save a file.
8. Save a file as new.
9. Invoke the help option, which provides information about other options in the system.<br>

**Admin Features:**

Upon initial startup, there is always one registered admin with the name *admin* and password *i<3c++*.

Each admin has the right to:

1. *Add a new user* – When adding a new user, information is requested about the type of user (admin or not), username (checked for uniqueness), and password.    
The username must not contain spaces and should be at least one character long. When provided, it is checked whether such a name already exists; if not, the new user is created.    
The password must not start or end with a space, must be at least one character long, and can contain letters (both uppercase and lowercase), digits, and spaces.    
3. *Remove a user* – When removing a user, the username of the user to be removed is requested.
4. *Add a book* – When adding a book, information is requested for the title, author, genre, rating, and year of publication.    
The title, author, and genre must not start or end with spaces and can only contain letters and spaces.    
Each of these should be at least one character long.    
The rating must be an integer between 0 and 5, and the year of publication must be greater than 0 and less than the current year.
6. *Remove a book* – When removing a book, the ID number of the book to be removed is requested.
7. *Add keywords to a book* – When adding keywords, the book ID is requested, and keywords are added until "exit" is typed.    
Each keyword must not start or end with spaces and must not contain spaces.
9. *Add a description to a book* – When adding a description, the book ID is requested, and the provided description is added, which must not start or end with spaces.<br>

**Any user who is not an admin has the right to:**

1. *Rate a book* – When rating a book, the book ID is requested. Once a user has rated a book, they cannot vote again for that same book.
The new vote is added to the existing rating and averaged. The vote must be an integer between 0 and 5.

Changes made can be saved to a binary file. Upon starting the program, a filename is required to open the specified file and work with the data from it.     
If the file is not saved after working with the program, the initial data will be restored upon the next startup.
