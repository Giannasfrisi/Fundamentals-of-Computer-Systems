import os
import statistics

# Get the absolute path to the file
file_path = os.path.abspath("server-output.txt")

try:
    with open(file_path, "r") as file:
        lines = file.readlines()

    # Initialize a list to store the differences
    differences = []

    # Iterate through lines and calculate differences
    for line in lines:
        # Split each line by ":" to separate the values
        parts = line.split(":")
        
        # Check if the line contains the expected format (e.g., "R0:")
        if len(parts) == 2 and parts[0].startswith("R"):
            values = parts[1].strip().split(",")
            
            # Ensure there are at least two values (e.g., "299069.635798420" and "299069.677749670")
            if len(values) >= 2:
                try:
                    # Extract the first and last values and convert them to floats
                    first_value = float(values[0])
                    last_value = float(values[-1])
                    
                    # Calculate the difference and add it to the list
                    difference = last_value - first_value
                    differences.append(difference)
                except ValueError:
                    # Handle cases where conversion to float fails
                    pass

    # Calculate average, maximum, minimum, and standard deviation
    if differences:
        average_difference = sum(differences) / len(differences)
        maximum_difference = max(differences)
        minimum_difference = min(differences)
        standard_deviation = statistics.stdev(differences)
        
        print("Average Difference:", average_difference)
        print("Maximum Difference:", maximum_difference)
        print("Minimum Difference:", minimum_difference)
        print("Standard Deviation of Differences:", standard_deviation)
    else:
        print("No valid differences found in the input file.")
except FileNotFoundError:
    print(f"The file '{file_path}' was not found.")