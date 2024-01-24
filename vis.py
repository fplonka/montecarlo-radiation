import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys
import numpy as np
file_name = sys.argv[1]

# Load data from CSV
data = pd.read_csv(file_name)

# Extract columns
hit_count = data['Radiation']
hit_count = np.log(hit_count)
hit_count = hit_count + abs(hit_count.min())
hit_count = 10 * hit_count
print(hit_count)
# hit_count *= 10 / max(hit_count)

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

ROOM_LENGTH_CM = 10.05 * 100
ROOM_WIDTH_CM = 5.50 * 100
ROOM_HEIGHT_CM = 3.22 * 100
ax.set_xlim(0, ROOM_WIDTH_CM)
ax.set_ylim(0, ROOM_LENGTH_CM)
ax.set_zlim(0, ROOM_HEIGHT_CM)
ax.set_box_aspect((ROOM_WIDTH_CM, ROOM_LENGTH_CM, ROOM_HEIGHT_CM))

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
