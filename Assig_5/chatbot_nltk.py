import nltk
from nltk.chat.util import Chat, reflections

# Movie data
movies = {
    'Interstellar': ['Morning: 10:00 AM', 'Afternoon: 2:00 PM', 'Evening: 6:00 PM'],
    'The Dark Knight': ['Morning: 11:00 AM', 'Afternoon: 3:00 PM', 'Evening: 7:00 PM'],
    'Dune': ['Morning: 9:30 AM', 'Afternoon: 1:30 PM', 'Evening: 5:30 PM']
}

# Patterns and responses
patterns = [
    (r'hi|hello|hey', ['Hello! How can I assist you today?']),
    (r'how are you', ['I am just a bot, but I am always ready to help you!']),
    (r'(.*) movie', [f"Here are the movies currently playing: {', '.join(movies.keys())}"]),
    (r'(.*) ticket', ['How many tickets would you like to book?']),
    (r'(.*) showtime', [f"Showtimes:\n" + "\n".join([f"{m}: {', '.join(t)}" for m, t in movies.items()])]),
    (r'(.*) timing', [f"Timings:\n" + "\n".join([f"{m}: {', '.join(t)}" for m, t in movies.items()])]),
    (r'(.*) (morning|afternoon|evening|night)', 
     ['We have slots in morning, afternoon, and evening. Which one suits you?']),
    (r'(.*) book tickets', ['Sure! Let’s proceed.']),
    (r'(.*) (bye|goodbye)', ['Goodbye! Enjoy your movie.'])
]

bot = Chat(patterns, reflections)

def book_tickets(movie, tickets, showtime):
    price = 100
    total = tickets * price
    return f"Booking confirmed! You have booked {tickets} tickets for {movie.title()} at {showtime}.\nTotal amount: Rs. {total}."

def main():
    print("ChatBot: Hello! Welcome to Movie Booking ChatBot.")
    while True:
        user_input = input("You: ")
        if not user_input.strip():
            continue
        
        if any(x in user_input.lower() for x in ['bye', 'goodbye']):
            print("ChatBot: Thanks! Have a great day.")
            break

        response = bot.respond(user_input)
        print("ChatBot:", response if response else "Sorry, I didn’t get that.")

        if 'book' in user_input.lower():
            movie = input("Which movie would you like to watch? :").title()
            tickets = input("How many tickets? :")
            try:
                tickets = int(tickets)
            except ValueError:
                print("ChatBot: Please enter a valid number.")
                continue
            showtime = input("Preferred time (e.g., Morning, Afternoon, Evening): ")
            print("ChatBot:", book_tickets(movie, tickets, showtime))

main()
