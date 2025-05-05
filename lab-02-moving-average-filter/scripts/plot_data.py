import os
import pandas as pd
import matplotlib.pyplot as plt

# Construct paths for the CSV files
data_file_path_original = os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "../data/temperature_data.csv"
)
data_file_path_filtered = os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "../data/filtered_data.csv"
)

# Load the data from CSV files into DataFrames
df_original = pd.read_csv(data_file_path_original)
df_filtered = pd.read_csv(data_file_path_filtered)

# Extract the filter type from the first row (assuming it is consistent across the file)
filter_type = df_filtered["FilterType"].iloc[0]

# Convert the 'DateTime' column to datetime objects for both DataFrames
df_original["DateTime"] = pd.to_datetime(df_original["DateTime"])
df_filtered["DateTime"] = pd.to_datetime(df_filtered["DateTime"])

# Set the 'DateTime' column as the index for both DataFrames
# inplace=True: Directly modifies the original DataFrame.
df_original.set_index("DateTime", inplace=True)
df_filtered.set_index("DateTime", inplace=True)

# Limit data for both DataFrames to a reasonable number of points
# .iloc[] allows integer-location based indexing to select rows and columns by index.
df_original_limited = df_original.iloc[::20]  # Select every 20th point
df_filtered_limited = df_filtered.iloc[::20]  # Select every 20th point

# Resample to daily frequency and calculate the mean
# df_original_daily = df_original.resample("D").mean()
# df_filtered_daily = df_filtered.resample("D").mean()

# Plot the temperature data from both DataFrames
plt.figure(figsize=(12, 6))  # Width: 12 inches, Height: 6 inches

# Plot the original data
plt.plot(
    df_original_limited.index,
    df_original_limited["Temperature (°C)"],
    # df_original_daily.index,
    # df_original_daily["Temperature (°C)"],
    linestyle="-",
    color="b",
    label="Original Temperature (°C)",
)

# Plot the filtered data
plt.plot(
    df_filtered_limited.index,
    df_filtered_limited["Temperature (°C)"],
    # df_filtered_daily.index,
    # df_filtered_daily["Temperature (°C)"],
    linestyle="-",
    color="r",
    label="Filtered Temperature (°C)",
)

# Add labels and title
plt.title(f"Temperature Over Time (Original with {filter_type} Filter)")
plt.ylabel("Temperature (°C)")
plt.xticks(rotation=45)  # Rotate x-axis labels for better visibility
plt.grid()
plt.legend()

# Adjust layout to prevent clipping of tick labels
plt.tight_layout()

# Show the plot
plt.show()
