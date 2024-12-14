from flask import Flask, render_template, request, redirect, url_for
import subprocess

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/calculate', methods=['POST'])
def calculate():
    # Get the form data
    source = request.form['source']
    destination = request.form['destination']

    # Call the backend C program to calculate the route
    result = subprocess.run(['./metro', source, destination], capture_output=True, text=True)
    output = result.stdout  # Capture the output from the C program

    # Parse the output to extract the route, distance, and fare
    route, distance, fare = parse_output(output)

    # Render the result page with the output and the map
    return render_template('result.html', output=output, route=route, fare=fare, distance=distance)

def parse_output(output):
    # Parse the output to extract the route, distance, and fare details
    route = []
    distance = 0
    fare = 0
    for line in output.split('\n'):
        if "->" in line:
            stations = line.split(" -> ")
            for station in stations:
                route.append(int(station.strip()))
        elif "Total distance" in line:
            distance = int(line.split(': ')[1].split(' ')[0])
        elif "Total fare" in line:
            fare = int(line.split(': ')[1].split(' ')[0])
    return route, distance, fare

if __name__ == '__main__':
    app.run(debug=True)
