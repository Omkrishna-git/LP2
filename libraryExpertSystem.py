class LibraryExpertSystem:
    def __init__(self):
        self.books = []
        self.load_default_books()

    def load_default_books(self):
        default_books = [
            # Computer Science Books
            ("Introduction to Python", "Computer Science", 1, "theory", "John Smith", "CS001", 5),
            ("Python Programming Lab", "Computer Science", 1, "practical", "Alice Johnson", "CS002", 3),
            ("Data Structures and Algorithms", "Computer Science", 2, "theory", "Robert Davis", "CS101", 4),
            ("Algorithm Design Manual", "Computer Science", 2, "theory", "Steven Skiena", "CS102", 2),
            ("Database Systems", "Computer Science", 3, "theory", "Raghu Ramakrishnan", "CS201", 3),
            ("Machine Learning Fundamentals", "Computer Science", 3, "theory", "Andrew Ng", "CS202", 6),
            ("AI Project Handbook", "Computer Science", 4, "project", "Peter Norvig", "CS301", 4),
            ("Cloud Computing Architecture", "Computer Science", 4, "theory", "Martin Kleppmann", "CS302", 3),

            # Electronics Books
            ("Basic Electronics", "Electronics", 1, "theory", "David Bell", "EL001", 5),
            ("Electronics Lab Manual", "Electronics", 1, "practical", "James Wilson", "EL002", 7),
            ("Digital Electronics", "Electronics", 2, "theory", "Morris Mano", "EL101", 4),
            ("Microprocessor Systems", "Electronics", 2, "theory", "Barry Brey", "EL102", 3),
            ("Embedded Systems Design", "Electronics", 3, "project", "Jonathan Valvano", "EL201", 5),
            ("VLSI Design", "Electronics", 3, "theory", "Neil Weste", "EL202", 2),
            ("IoT Implementation Guide", "Electronics", 4, "project", "Samuel Greengard", "EL301", 4),
            ("Advanced Circuit Theory", "Electronics", 4, "theory", "Charles Desoer", "EL302", 3),

            # IT Books
            ("Web Development Basics", "IT", 1, "theory", "Jennifer Robbins", "IT001", 4),
            ("Networking Essentials", "IT", 1, "theory", "Cisco Press", "IT002", 6),
            ("System Administration", "IT", 2, "practical", "Mark Minasi", "IT101", 3),
            ("Cybersecurity Principles", "IT", 2, "theory", "William Stallings", "IT102", 5),
            ("Cloud Deployment Strategies", "IT", 3, "project", "Thomas Erl", "IT201", 4),
            ("Big Data Analytics", "IT", 3, "theory", "Anand Rajaraman", "IT202", 3),
            ("DevOps Handbook", "IT", 4, "theory", "Gene Kim", "IT301", 5),
            ("Blockchain Technologies", "IT", 4, "project", "Andreas Antonopoulos", "IT302", 2)
        ]
        for book in default_books:
            self.add_book(*book)

    def add_book(self, title, subject, year, book_type, author, book_id, copies):
        self.books.append({
            "title": title,
            "subject": subject.lower(),
            "year": int(year),
            "type": book_type.lower(),
            "author": author,
            "id": book_id.upper(),
            "copies": int(copies),
            "available": int(copies)
        })

    def recommend_books(self, subject=None, year=None, book_type=None, author=None):
        recommendations = []
        
        for book in self.books:
            match = True
            if subject and book["subject"] != subject.lower():
                match = False
            if year and book["year"] != int(year):
                match = False
            if book_type and book["type"] != book_type.lower():
                match = False
            if author and author.lower() not in book["author"].lower():
                match = False
            if match and book["available"] > 0:
                recommendations.append(book)

        return recommendations

    def display_books(self, books):
        if not books:
            print("\n╔" + "═"*50 + "╗")
            print("║" + "NO BOOKS FOUND".center(50) + "║")
            print("╚" + "═"*50 + "╝")
            return

        print("\n╔" + "═"*88 + "╗")
        print("║" + "LIBRARY BOOK RECOMMENDATIONS".center(88) + "║")
        print("╠" + "═"*88 + "╣")
        print("║ {:<4} {:<25} {:<20} {:<8} {:<12} {:<10} {:<8} ║".format(
            "No.", "Title", "Author", "Year", "Type", "Book ID", "Available"))
        print("╠" + "═"*88 + "╣")
        
        for i, book in enumerate(books, 1):
            print("║ {:<4} {:<25} {:<20} {:<8} {:<12} {:<10} {:<8} ║".format(
                i,
                book['title'][:22] + '...' if len(book['title']) > 25 else book['title'],
                book['author'][:17] + '...' if len(book['author']) > 20 else book['author'],
                book['year'],
                book['type'].capitalize(),
                book['id'],
                f"{book['available']}/{book['copies']}"
            ))
        print("╚" + "═"*88 + "╝")

    def checkout_book(self, book_id):
        for book in self.books:
            if book["id"] == book_id.upper() and book["available"] > 0:
                book["available"] -= 1
                return True
        return False

def run_library_expert_system():
    system = LibraryExpertSystem()

    print("\n" + "╔" + "═"*50 + "╗")
    print("║" + "LIBRARY EXPERT SYSTEM".center(50) + "║")
    print("╚" + "═"*50 + "╝")

    while True:
        print("\n" + "═"*20 + " MAIN MENU " + "═"*20)
        print("1. Search Books")
        print("2. Add New Book")
        print("3. Checkout Book")
        print("4. Exit")
        print("═"*51)
        
        choice = input("Select an option (1-4): ").strip()

        if choice == '1':
            print("\n" + "═"*20 + " SEARCH BOOKS " + "═"*20)
            print("Leave any field blank to skip that filter")
            subject = input("Subject (CS/Electronics/IT): ").strip()
            year = input("Year (1-4): ").strip()
            book_type = input("Type (theory/practical/project): ").strip()
            author = input("Author name: ").strip()
            
            results = system.recommend_books(
                subject if subject else None,
                year if year else None,
                book_type if book_type else None,
                author if author else None
            )
            system.display_books(results)

        elif choice == '2':
            print("\n" + "═"*20 + " ADD NEW BOOK " + "═"*20)
            title = input("Title: ").strip()
            subject = input("Subject: ").strip()
            year = input("Year: ").strip()
            book_type = input("Type: ").strip()
            author = input("Author: ").strip()
            book_id = input("Book ID: ").strip()
            copies = input("Number of copies: ").strip()
            
            system.add_book(title, subject, year, book_type, author, book_id, copies)
            print(f"\nBook '{title}' added successfully with {copies} copies.")

        elif choice == '3':
            print("\n" + "═"*20 + " CHECKOUT BOOK " + "═"*20)
            book_id = input("Enter Book ID to checkout: ").strip()
            if system.checkout_book(book_id):
                print(f"\nBook {book_id} checked out successfully.")
            else:
                print(f"\nBook {book_id} not available or doesn't exist.")

        elif choice == '4':
            print("\n" + "═"*20 + " THANK YOU " + "═"*20)
            print("Exiting Library Expert System. Goodbye!")
            break

        else:
            print("\nInvalid choice. Please select 1-4.")

if __name__ == "__main__":
    run_library_expert_system()