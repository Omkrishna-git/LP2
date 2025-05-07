import pandas as pd

# Rules for evaluation
rules = {
    "rule1": ("Meets all project deadlines", 20),
    "rule2": ("Exceeds expectations", 30),
    "rule3": ("Shows initiative and takes on additional responsibilities", 15),
    "rule4": ("Collaborates well in a team", 10),
    "rule5": ("Is always punctual", 10),
    "rule6": ("Receives positive client feedback", 15),
    "rule7": ("Brings new ideas and innovations", 20),
    "rule8": ("Frequently absent or misses deadlines", -25),
    "rule9": ("Consistently performs below expectations", -35),
    "rule10": ("Demonstrates leadership qualities", 25),
    "rule11": ("Regularly meets KPIs and targets", 20),
    "rule12": ("Active participation in meetings", 10),
    "rule13": ("Maintains strong documentation and reporting practices", 15),
    "rule14": ("Demonstrates poor communication skills", -20),
    "rule15": ("Misses meetings without notice", -15),
    "rule16": ("Displays unprofessional behavior", -30)
}

def get_employee_details():
    name = input("Enter Employee Name: ").strip()
    position = input("Enter Current Position: ").strip()
    experience = input("Enter Years of Experience: ").strip()
    work_mode = input("Enter Work Mode (Remote / On-Site / Hybrid): ").strip()

    if not name or not position or not experience:
        raise ValueError("All fields are required.")

    return name, position, work_mode, experience

def get_manager_assessment():
    print("\nManager's Review (enter 1 for Yes, 0 for No):")
    score = 0
    for key, (desc, points) in rules.items():
        while True:
            try:
                value = int(input(f"{desc}? (0/1): "))
                if value in [0, 1]:
                    score += value * points
                    break
                else:
                    print("Please enter 0 or 1.")
            except ValueError:
                print("Invalid input. Please enter 0 or 1.")
    return score

def evaluate_performance(score):
    if score >= 100:
        rating = "Excellent"
        recommendation = "Highly recommended for promotion and incentive increment."
        improvement = "Keep up the great work and consider mentoring junior employees."
    elif score >= 80:
        rating = "Very Good"
        recommendation = "Eligible for incentives; potential for promotion with continued improvement."
        improvement = "Work on leadership and strategic thinking to strengthen promotion chances."
    elif score >= 60:
        rating = "Good"
        recommendation = "Performing well; some improvement will enhance growth opportunities."
        improvement = "Take initiative on more tasks and improve collaboration."
    elif score >= 40:
        rating = "Average"
        recommendation = "No immediate promotion; requires improvement in several areas."
        improvement = "Focus on punctuality, quality of work, and better communication."
    else:
        rating = "Needs Improvement"
        recommendation = "Possible risk of demotion or performance review required."
        improvement = "Improve consistency, time management, and client interactions."
    return rating, recommendation, improvement


def save_to_history(name, position, work_mode, experience, score, rating, recommendation, feedback):
    data = {
        "Employee Name": [name],
        "Position": [position],
        "Work Mode": [work_mode],
        "Experience": [experience],
        "Score": [score],
        "Rating": [rating],
        "Recommendation": [recommendation],
        "Feedback": [feedback]
    }
    df = pd.DataFrame(data)
    try:
        existing_df = pd.read_csv("performance_history.csv")
        df = pd.concat([existing_df, df], ignore_index=True)
    except FileNotFoundError:
        pass
    df.to_csv("performance_history.csv", index=False)
    print("\nSaved to performance_history.csv")

def main():
    try:
        name, position, work_mode, experience = get_employee_details()
        score = get_manager_assessment()
        rating, recommendation, improvement = evaluate_performance(score)
        feedback = input("\nEnter Manager's Feedback: ").strip()

        print("\n----- Performance Evaluation -----")
        print(f"Employee: {name}")
        print(f"Position: {position}")
        print(f"Experience: {experience} years")
        print(f"Work Mode: {work_mode}")
        print(f"Final Score: {score}")
        print(f"Performance Rating: {rating}")
        print(f"Recommendation: {recommendation}")
        print(f"Improvement Suggestions: {improvement}")
        print(f"Manager Feedback: {feedback}")
        print("----------------------------------")

        save_to_history(name, position, work_mode, experience, score, rating, recommendation, feedback)

    except ValueError as e:
        print(f"\nError: {e}")

if __name__ == "__main__":
    main()
