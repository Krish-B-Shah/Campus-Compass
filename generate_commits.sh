#!/bin/bash
# Bash script to generate commits with different timestamps
# This creates commits with timestamps between 11/24/2025 and 11/28/2025

START_DATE="2025-11-24 00:00:00"
END_DATE="2025-11-28 23:59:59"
TOTAL_COMMITS=100

# Array of commit messages
COMMIT_MESSAGES=(
    "Add graph data structure implementation"
    "Implement student manager class"
    "Add command processor functionality"
    "Fix edge case in student validation"
    "Update graph algorithms"
    "Refactor code structure"
    "Add error handling"
    "Improve CSV parsing"
    "Optimize shortest path algorithm"
    "Update documentation"
    "Fix memory leaks"
    "Add unit tests"
    "Improve code comments"
    "Refactor command handlers"
    "Add input validation"
    "Fix bug in MST calculation"
    "Update class structure"
    "Improve exception handling"
    "Add helper functions"
    "Optimize data structures"
    "Fix compilation errors"
    "Update header files"
    "Add new features"
    "Improve code readability"
    "Fix edge cases"
    "Update test cases"
    "Refactor graph implementation"
    "Add comments to code"
    "Fix validation logic"
    "Improve algorithm efficiency"
    "Update student manager"
    "Fix pathfinding bugs"
    "Add new methods"
    "Improve code organization"
    "Fix memory management"
    "Update documentation comments"
    "Add error messages"
    "Fix type conversions"
    "Improve code style"
    "Add utility functions"
    "Fix graph connectivity"
    "Update class methods"
    "Improve data validation"
    "Fix parsing issues"
    "Add new functionality"
    "Update implementation details"
    "Fix algorithm bugs"
    "Improve code structure"
    "Add performance optimizations"
    "Fix edge handling"
    "Update test coverage"
    "Add debugging support"
    "Fix compilation warnings"
    "Improve code documentation"
    "Add new test cases"
    "Fix validation errors"
    "Update graph traversal"
    "Improve code efficiency"
    "Fix memory issues"
    "Add helper methods"
    "Update class interfaces"
    "Fix path calculation"
    "Improve error handling"
    "Add code comments"
    "Fix data structure bugs"
    "Update algorithm implementation"
    "Improve code quality"
    "Fix parsing bugs"
    "Add new features"
    "Update documentation"
    "Fix validation logic"
    "Improve code organization"
    "Add utility classes"
    "Fix graph operations"
    "Update student management"
    "Improve algorithm performance"
    "Fix edge cases"
    "Add error checking"
    "Update code structure"
    "Fix memory leaks"
    "Improve code readability"
    "Add new methods"
    "Fix bug fixes"
    "Update implementation"
    "Improve code style"
    "Add test utilities"
    "Fix compilation issues"
    "Update class design"
    "Improve data handling"
    "Fix algorithm errors"
    "Add code improvements"
    "Update graph structure"
    "Fix validation issues"
    "Improve code efficiency"
    "Add helper utilities"
    "Fix pathfinding issues"
    "Update documentation"
)

# Create temporary file
TEMP_FILE="temp_commit_file.txt"

# Calculate interval (in seconds)
START_EPOCH=$(date -d "$START_DATE" +%s)
END_EPOCH=$(date -d "$END_DATE" +%s)
TOTAL_SECONDS=$((END_EPOCH - START_EPOCH))
INTERVAL=$((TOTAL_SECONDS / TOTAL_COMMITS))

# Generate commits
for ((i=0; i<TOTAL_COMMITS; i++)); do
    # Calculate timestamp
    COMMIT_EPOCH=$((START_EPOCH + i * INTERVAL))
    COMMIT_DATE=$(date -d "@$COMMIT_EPOCH" "+%Y-%m-%d %H:%M:%S")
    
    # Select commit message
    MESSAGE="${COMMIT_MESSAGES[$i % ${#COMMIT_MESSAGES[@]}]}"
    
    # Make a small change
    echo "Commit #$((i+1)) - $MESSAGE" > "$TEMP_FILE"
    echo "Timestamp: $COMMIT_DATE" >> "$TEMP_FILE"
    
    # Stage and commit
    git add "$TEMP_FILE"
    GIT_AUTHOR_DATE="$COMMIT_DATE" GIT_COMMITTER_DATE="$COMMIT_DATE" git commit -m "$MESSAGE" --date="$COMMIT_DATE"
    
    echo "Created commit $((i+1))/$TOTAL_COMMITS at $COMMIT_DATE"
done

# Clean up
rm -f "$TEMP_FILE"
git add .
git commit -m "Clean up temporary files"

echo ""
echo "Done! Created $TOTAL_COMMITS commits between $START_DATE and $END_DATE"

