import streamlit as st
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

chatbot = Chat(patterns, reflections)

# Ticket booking logic
def book_tickets(movie, tickets, showtime):
    price = 100
    total = tickets * price
    return f"Booking confirmed! You have booked {tickets} tickets for {movie.title()} at {showtime}.\nTotal amount: Rs. {total}."

# --- Streamlit UI ---
st.title("🎬 Movie Ticket Booking ChatBot")

if "history" not in st.session_state:
    st.session_state.history = []
if "booking_stage" not in st.session_state:
    st.session_state.booking_stage = None
if "movie" not in st.session_state:
    st.session_state.movie = ""
if "tickets" not in st.session_state:
    st.session_state.tickets = 0
if "showtime" not in st.session_state:
    st.session_state.showtime = ""

user_input = st.chat_input("Say something...")

if user_input:
    st.session_state.history.append(("user", user_input))

    # Booking flow logic
    if st.session_state.booking_stage == "movie":
        st.session_state.movie = user_input.title()
        st.session_state.booking_stage = "tickets"
        st.session_state.history.append(("bot", "How many tickets?"))

    elif st.session_state.booking_stage == "tickets":
        try:
            st.session_state.tickets = int(user_input)
            st.session_state.booking_stage = "showtime"
            st.session_state.history.append(("bot", "Preferred showtime?"))
        except:
            st.session_state.history.append(("bot", "Please enter a valid number."))

    elif st.session_state.booking_stage == "showtime":
        st.session_state.showtime = user_input
        response = book_tickets(st.session_state.movie, st.session_state.tickets, st.session_state.showtime)
        st.session_state.history.append(("bot", response))
        st.session_state.booking_stage = None  # reset

    elif "book" in user_input.lower():
        st.session_state.booking_stage = "movie"
        st.session_state.history.append(("bot", "Which movie would you like to watch?"))

    else:
        response = chatbot.respond(user_input)
        st.session_state.history.append(("bot", response if response else "Sorry, I didn’t get that."))

# Show chat history
for speaker, message in st.session_state.history:
    if speaker == "user":
        with st.chat_message("user"):
            st.markdown(message)
    else:
        with st.chat_message("assistant"):
            st.markdown(message)
