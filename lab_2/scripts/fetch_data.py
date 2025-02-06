import os
import requests
import csv
from datetime import datetime, timedelta

# Get the directory of the current script
current_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the path to the data directory
data_file_path = os.path.join(current_dir, "../data/temperature_data.csv")

# Latitude and longitude for Turku
latitude = 60.4518
longitude = 22.2666

# Set end date as two days ago from now
end_date = datetime.now() - timedelta(days=2)

# Calculate the start date as one year before the end date
start_date = end_date - timedelta(days=365)

# Format dates as YYYY-MM-DD
start_date_str = start_date.strftime("%Y-%m-%d")
end_date_str = end_date.strftime("%Y-%m-%d")

# Open-Meteo API endpoint for weather data
url = f"https://archive-api.open-meteo.com/v1/era5?latitude={latitude}&longitude={longitude}&start_date={start_date_str}&end_date={end_date_str}&hourly=temperature_2m"

# Send a GET request to the API
response = requests.get(url)

# Check if the request was successful
if response.status_code == 200:
    data = response.json()  # Parse JSON response

    # Get the data
    dates = data["hourly"]["time"]
    temperatures = data["hourly"]["temperature_2m"]

    # Limit to the last 100 entries
    # last_100_dates = dates[-100:]
    # last_100_temperatures = temperatures[-100:]

    # Append the data to the CSV file
    with open(data_file_path, mode="w", newline="") as file:
        writer = csv.writer(file)
        # Header
        writer.writerow(["DateTime", "Temperature (°C)"])
        # Write the data rows
        for date, temp in zip(dates, temperatures):
            # for date, temp in zip(last_100_dates, last_100_temperatures):
            writer.writerow([date, temp])

    print(f"Data added to {os.path.basename(data_file_path)}")
else:
    print(f"Error fetching data: {response.status_code}")
