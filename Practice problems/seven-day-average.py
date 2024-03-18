import csv
import requests
import copy


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases={}
    previous_cases={}
    for line in reader:
        if line['state'] not in previous_cases:
            previous_cases[line['state']] = {}
        previous_cases[line['state']][line['date']] = line['cases']
    for i in previous_cases:
        new_cases[i]=[]
        for _ in range(15):
            x=previous_cases[i].pop(max(previous_cases[i]), None)
            new_cases[i].append(int(x))
    temp=copy.deepcopy(new_cases)
    for case in new_cases:
        for i in range(1,len(new_cases[case])):
            new_cases[case][i]-=temp[case][i-1]
            new_cases[case][i]*=-1
        del new_cases[case][0]
    return new_cases







# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    lastweek={}
    for state in states:
        lastweek[state]=sum(new_cases[state][7:14])/7
    secondlastweek={}
    for state in states:
        secondlastweek[state]=sum(new_cases[state][0:7])/7
    for state in lastweek:
        if lastweek[state]>secondlastweek[state]:
            upordown="increase"
            try:
                percent= ((lastweek[state]/secondlastweek[state])-1)*100
            except ZeroDivisionError:
                percent=100
        else:
            upordown="decrease"
            try:
                percent= ((secondlastweek[state]/lastweek[state])-1)*100
            except ZeroDivisionError:
                percent=100
        print(f"{state} had a 7-day average of {int(lastweek[state])} and a {upordown} of {int(percent)}%")

main()
