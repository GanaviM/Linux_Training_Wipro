# Run a command (replace command with your actual command)
ls

# Check the exit status
if [ $? -eq 0 ]; then
  echo "Command executed successfully."
else
  echo "Command failed with exit status: $?."
fi

# Print the name of the script
echo "This script is called: $0"

# Log information with the script name
echo "$(date): $0 - Processing data..." >> log.txt

# Check if the script received at least two arguments
if [ $# -lt 2 ]; then
  echo "Usage: $0 <filename> <destination>"
  exit 1  # Exit with an error code if not enough arguments
fi

# Process the first two arguments
filename="$1"
destination="$2"

# ... (rest of your script using $filename and $destination)
