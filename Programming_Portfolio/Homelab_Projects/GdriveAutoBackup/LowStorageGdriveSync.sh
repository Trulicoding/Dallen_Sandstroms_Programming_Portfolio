#!/bin/bash

# Backup creation
BACKUP_DIR="" # Example: "/path/to/backups"
TIMESTAMP=$(date +"%m-%d-%Y_Backup")
NEW_FOLDER="$BACKUP_DIR/$TIMESTAMP"
ZIPFILE="$BACKUP_DIR/$TIMESTAMP.zip"
DIRECTORIES_TO_BACKUP=(
    # Example: "/path/to/Documents"
)

# Ensure backup directory exists
mkdir -p "$BACKUP_DIR"

# Move previous contents into a timestamped folder
if [ "$(ls -A "$BACKUP_DIR" 2>/dev/null)" ]; then
    mkdir -p "$NEW_FOLDER"
    mv "$BACKUP_DIR"/* "$NEW_FOLDER" 2>/dev/null
fi

# Create the zipped backup
echo "Creating backup at $ZIPFILE..."
zip -r "$ZIPFILE" "${DIRECTORIES_TO_BACKUP[@]}" > /dev/null 2>&1

# Verify if the zip was successful
if [ $? -eq 0 ]; then
    echo "Backup created successfully: $ZIPFILE"
else
    echo "Error: Backup failed at $(date)"
    exit 1
fi

# Remove the old folder after successful execution
if [ -d "$NEW_FOLDER" ]; then
    rm -rf "$NEW_FOLDER"
fi

echo "Backup process completed."

# Sync to Google Drive with deduplication
LOCAL_DIR="" # Example: "/path/to/local"
REMOTE_DIR="" # Example: "gdrive:/path/to/remote"
RCLONE_CONFIG="" # Example: "/path/to/rclone.conf"

# Remove duplicates in the remote directory
rclone --config "$RCLONE_CONFIG" dedupe "$REMOTE_DIR" --dedupe-mode newest

# Sync local directory to remote, skipping symbolic links and bypassing trash
rclone --config "$RCLONE_CONFIG" sync "$LOCAL_DIR" "$REMOTE_DIR" --delete-before --progress --drive-use-trash=false

# Check if the sync succeeded
if [ $? -ne 0 ]; then
    echo "Error: Sync failed at $(date)"
    exit 1
fi

echo "Sync completed successfully at $(date)"
