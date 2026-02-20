
#include <iostream>
#include <string>
using namespace std;

struct Book {
  int id;
  string title;
  string author;
  bool isIssued;
};

Book library[100];
int bookCount = 0;

void printLine() {
  for (int i = 0; i < 50; i++)
    cout << "-";
  cout << endl;
}

int findBook(int id) {
  for (int i = 0; i < bookCount; i++) {
    if (library[i].id == id)
      return i;
  }
  return -1;
}

void addBook() {
  cout << "\n--- Add New Book ---\n";

  int id;
  cout << "Enter Book ID: ";
  cin >> id;

  if (findBook(id) != -1) {
    cout << "Error: A book with this ID already exists!\n";
    return;
  }

  library[bookCount].id = id;
  cin.ignore();
  cout << "Enter Book Title: ";
  getline(cin, library[bookCount].title);
  cout << "Enter Book Author: ";
  getline(cin, library[bookCount].author);
  library[bookCount].isIssued = false;

  cout << "Book '" << library[bookCount].title << "' added successfully!\n";
  bookCount++;
}

void issueBook() {
  if (bookCount == 0) {
    cout << "\nNo books in the library.\n";
    return;
  }

  int id;
  cout << "\n--- Issue Book ---\n";
  cout << "Enter Book ID to issue: ";
  cin >> id;

  int index = findBook(id);
  if (index == -1) {
    cout << "Book not found.\n";
  } else if (library[index].isIssued) {
    cout << "Book '" << library[index].title << "' is already issued.\n";
  } else {
    library[index].isIssued = true;
    cout << "Book '" << library[index].title << "' issued successfully!\n";
  }
}

void returnBook() {
  if (bookCount == 0) {
    cout << "\nNo books in the library.\n";
    return;
  }

  int id;
  cout << "\n--- Return Book ---\n";
  cout << "Enter Book ID to return: ";
  cin >> id;

  int index = findBook(id);
  if (index == -1) {
    cout << "Book not found.\n";
  } else if (!library[index].isIssued) {
    cout << "Book '" << library[index].title << "' was not issued.\n";
  } else {
    library[index].isIssued = false;
    cout << "Book '" << library[index].title << "' returned successfully!\n";
  }
}

void displayBooks() {
  if (bookCount == 0) {
    cout << "\nNo books in the library.\n";
    return;
  }

  int available = 0, issued = 0;
  for (int i = 0; i < bookCount; i++) {
    if (library[i].isIssued)
      issued++;
    else
      available++;
  }

  cout << "\n--- Library Inventory ---\n";
  cout << "Total: " << bookCount << " | Available: " << available
       << " | Issued: " << issued << endl;
  printLine();

  for (int i = 0; i < bookCount; i++) {
    cout << "ID: " << library[i].id << " | Title: " << library[i].title
         << " | Author: " << library[i].author
         << " | Status: " << (library[i].isIssued ? "Issued" : "Available")
         << endl;
  }
  printLine();
}

void searchBook() {
  if (bookCount == 0) {
    cout << "\nNo books in the library.\n";
    return;
  }

  string keyword;
  cout << "\n--- Search Book ---\n";
  cin.ignore();
  cout << "Enter title or author to search: ";
  getline(cin, keyword);

  string lowerKey = keyword;
  for (int i = 0; i < lowerKey.length(); i++)
    lowerKey[i] = tolower(lowerKey[i]);

  bool found = false;
  for (int i = 0; i < bookCount; i++) {
    string lowerTitle = library[i].title;
    string lowerAuthor = library[i].author;
    for (int j = 0; j < lowerTitle.length(); j++)
      lowerTitle[j] = tolower(lowerTitle[j]);
    for (int j = 0; j < lowerAuthor.length(); j++)
      lowerAuthor[j] = tolower(lowerAuthor[j]);

    if (lowerTitle.find(lowerKey) != string::npos ||
        lowerAuthor.find(lowerKey) != string::npos) {
      if (!found) {
        cout << "\nSearch Results:\n";
        printLine();
        found = true;
      }
      cout << "ID: " << library[i].id << " | Title: " << library[i].title
           << " | Author: " << library[i].author
           << " | Status: " << (library[i].isIssued ? "Issued" : "Available")
           << endl;
    }
  }

  if (!found)
    cout << "No books found matching '" << keyword << "'.\n";
}

void deleteBook() {
  if (bookCount == 0) {
    cout << "\nNo books in the library.\n";
    return;
  }

  int id;
  cout << "\n--- Delete Book ---\n";
  cout << "Enter Book ID to delete: ";
  cin >> id;

  int index = findBook(id);
  if (index == -1) {
    cout << "Book not found.\n";
  } else {
    string title = library[index].title;
    for (int i = index; i < bookCount - 1; i++)
      library[i] = library[i + 1];
    bookCount--;
    cout << "Book '" << title << "' deleted successfully!\n";
  }
}

int main() {
  int choice;

  cout << "\n";
  printLine();
  cout << "     LIBRARY MANAGEMENT SYSTEM\n";
  printLine();

  do {
    cout << "\n";
    printLine();
    cout << "  1. Add New Book\n";
    cout << "  2. Issue Book\n";
    cout << "  3. Return Book\n";
    cout << "  4. Display All Books\n";
    cout << "  5. Search Book\n";
    cout << "  6. Delete Book\n";
    cout << "  7. Exit\n";
    printLine();
    cout << "  Enter your choice: ";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid input! Please enter a number.\n";
      continue;
    }

    switch (choice) {
    case 1:
      addBook();
      break;
    case 2:
      issueBook();
      break;
    case 3:
      returnBook();
      break;
    case 4:
      displayBooks();
      break;
    case 5:
      searchBook();
      break;
    case 6:
      deleteBook();
      break;
    case 7:
      cout << "\nThank you for using Library Management System!\n";
      cout << "Goodbye!\n";
      break;
    default:
      cout << "Invalid choice! Please enter 1-7.\n";
    }
  } while (choice != 7);

  return 0;
}
