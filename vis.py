import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load data from CSV
data = pd.read_csv('sensor_data.csv')

# Extract columns
hit_count = data['HitCount']
x = data['PositionX']
y = data['PositionY']
z = data['PositionZ']

# Create a 3D scatter plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot each sensor as a point in the scatter plot
# Size of each point is proportional to the hit count
scatter = ax.scatter(x, y, z, s=hit_count, c=hit_count,
                     cmap='viridis', alpha=0.6, edgecolors='w')

# Add labels and title
ax.set_xlabel('X Position (cm)')
ax.set_ylabel('Y Position (cm)')
ax.set_zlabel('Z Position (cm)')
ax.set_title('Radiation Hit Count per Sensor')

# Add a color bar
cbar = plt.colorbar(scatter, ax=ax)
cbar.set_label('Hit Count')

# Show the plot
plt.show()
