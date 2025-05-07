def getDay(dateday):
    if "Monday" in dateday:
        return "Monday"
    elif "Tuesday" in dateday:
        return "Tuesday"
    elif "Wednesday" in dateday:
        return "Wednesday"
    elif "Thursday" in dateday:
        return "Thursday"
    elif "Friday" in dateday:
        return "Friday"
    elif "Saturday" in dateday:
        return "Saturday"
    elif "Sunday" in dateday:
        return "Sunday"

def getbill(ans, e, u):
  print(f"{e}: Enter details (consumer id)")
  id=input(f"{u}:")
  return f"Complaint registered successfully for consumer id {id}"

def waterdept(ans, e, u):
    if "no" in ans:
        print(f"{e}: Let me know the details (date, day)")
        dateday = input(f"{u}: ")
        day = getDay(dateday)
        if "Monday" in dateday or "Wednesday" in dateday or "Friday" in dateday:
            return f"No water supply on {dateday} due to pipeline work"
        elif "Tuesday" in dateday or "Thursday" in dateday or "Saturday" in dateday:
            return f"No water supply on {dateday} due to blockage"
        else:
            return "No water supply on {dateday} due to tank cleaning"
    elif "when" in ans:
        return "The water supply should be regulated within 2 days. Please contact the department if the problem persists"



def lightdept(ans, e, u):
    if "no lights" in ans:
        print(f"{e}: Let me know the details (date, day)")
        dateday = input(f"{u}: ")
        if dateday == "Monday" or dateday == "Wednesday" or dateday == "Friday":
            return f"No electricity supply on {dateday} due to road work"
        elif dateday == "Tuesday" or dateday == "Thursday" or dateday == "Saturday":
            return f"No electricity supply on {dateday} due to wire damage"
        else:
            return f"No electricity supply on {dateday} due to load shedding"
    elif "when" in ans and "lights" in ans:
        return "The electricity supply will be regulated within few days.Please contact the department if the problem persists"


def answer(ans, e, u):
    if ans == "hi" or ans == "hello" or ans == "hey":
        return "How may I help you?"
    elif ans == "bye" or ans == "exit" or ans == "quit":
        return "Bye! Have a good day!"
    elif "no water" in ans:
        return waterdept(ans, e, u)
    elif "no lights" in ans:
        return lightdept(ans, e, u)
    elif ("when" in ans) and ("water" in ans):
        return waterdept(ans, e, u)
    elif ("when" in ans) and ("lights" in ans or "light" in ans or "electricity" in ans):
        return lightdept(ans, e, u)
    elif "bill" in ans:
      return getbill(ans, e, u)
    else:
      return "You can contact the customer grievance department on 1800-080-080"

e = "Expert"
u = "You"
print(f"{e}: Hey there!")
while True:
    user_input = input(f"{u}: ")
    resp = answer(user_input, e, u)
    print(f"{e}: {resp}")
    if resp == "Bye! Have a good day!":
        break



# Expert: Hey there!
# You: hi
# Expert: How may I help you?
# You: why no water supply on Monday
# Expert: Let me know the details (date, day)
# You: 21 April Monday
# Expert: No water supply on 21 April Monday due to pipeline work
# You: when water supply resume?
# Expert: The water supply should be regulated within 2 days. Please contact the department if the problem persists
# You: why no lights in passage?
# Expert: Let me know the details (date, day)
# You: 20 April Sunday
# Expert: No electricity supply on 20 April Sunday due to load shedding
# You: when will lights supply resume?
# Expert: The electricity supply will be regulated within few days.Please contact the department if the problem persists
# You: i have issue in my bill
# Expert: Enter details (consumer id)
# You:2394947
# Expert: Complaint registered successfully for consumer id 2394947
# You: bye
# Expert: Bye! Have a good day!