# PowerShell script to generate commits with different timestamps
# This creates commits with timestamps between 11/24/2025 and 11/28/2025

$startDate = Get-Date "2025-11-24 00:00:00"
$endDate = Get-Date "2025-11-28 23:59:59"
$totalCommits = 100

# Calculate time span
$timeSpan = $endDate - $startDate
$intervalMinutes = [math]::Floor($timeSpan.TotalMinutes / $totalCommits)

$commitMessages = @(
    "Add graph data structure implementation",
    "Implement student manager class",
    "Add command processor functionality",
    "Fix edge case in student validation",
    "Update graph algorithms",
    "Refactor code structure",
    "Add error handling",
    "Improve CSV parsing",
    "Optimize shortest path algorithm",
    "Update documentation",
    "Fix memory leaks",
    "Add unit tests",
    "Improve code comments",
    "Refactor command handlers",
    "Add input validation",
    "Fix bug in MST calculation",
    "Update class structure",
    "Improve exception handling",
    "Add helper functions",
    "Optimize data structures",
    "Fix compilation errors",
    "Update header files",
    "Add new features",
    "Improve code readability",
    "Fix edge cases",
    "Update test cases",
    "Refactor graph implementation",
    "Add comments to code",
    "Fix validation logic",
    "Improve algorithm efficiency",
    "Update student manager",
    "Fix pathfinding bugs",
    "Add new methods",
    "Improve code organization",
    "Fix memory management",
    "Update documentation comments",
    "Add error messages",
    "Fix type conversions",
    "Improve code style",
    "Add utility functions",
    "Fix graph connectivity",
    "Update class methods",
    "Improve data validation",
    "Fix parsing issues",
    "Add new functionality",
    "Update implementation details",
    "Fix algorithm bugs",
    "Improve code structure",
    "Add performance optimizations",
    "Fix edge handling",
    "Update test coverage",
    "Add debugging support",
    "Fix compilation warnings",
    "Improve code documentation",
    "Add new test cases",
    "Fix validation errors",
    "Update graph traversal",
    "Improve code efficiency",
    "Fix memory issues",
    "Add helper methods",
    "Update class interfaces",
    "Fix path calculation",
    "Improve error handling",
    "Add code comments",
    "Fix data structure bugs",
    "Update algorithm implementation",
    "Improve code quality",
    "Fix parsing bugs",
    "Add new features",
    "Update documentation",
    "Fix validation logic",
    "Improve code organization",
    "Add utility classes",
    "Fix graph operations",
    "Update student management",
    "Improve algorithm performance",
    "Fix edge cases",
    "Add error checking",
    "Update code structure",
    "Fix memory leaks",
    "Improve code readability",
    "Add new methods",
    "Fix bug fixes",
    "Update implementation",
    "Improve code style",
    "Add test utilities",
    "Fix compilation issues",
    "Update class design",
    "Improve data handling",
    "Fix algorithm errors",
    "Add code improvements",
    "Update graph structure",
    "Fix validation issues",
    "Improve code efficiency",
    "Add helper utilities",
    "Fix pathfinding issues",
    "Update documentation"
)

# Create a temporary file to modify for commits
$tempFile = "temp_commit_file.txt"

# Generate commits
for ($i = 0; $i -lt $totalCommits; $i++) {
    # Calculate timestamp for this commit
    $commitDate = $startDate.AddMinutes($i * $intervalMinutes)
    
    # Format date for git
    $gitDate = $commitDate.ToString("yyyy-MM-dd HH:mm:ss")
    
    # Select a random commit message
    $message = $commitMessages[$i % $commitMessages.Length]
    
    # Make a small change to trigger commit
    $content = "Commit #$($i + 1) - $message`nTimestamp: $gitDate`n"
    Set-Content -Path $tempFile -Value $content
    
    # Stage the file
    git add $tempFile
    
    # Create commit with specific date
    $env:GIT_AUTHOR_DATE = $gitDate
    $env:GIT_COMMITTER_DATE = $gitDate
    git commit -m "$message" --date="$gitDate"
    
    Write-Host "Created commit $($i + 1)/$totalCommits at $gitDate"
}

# Clean up temporary file
Remove-Item $tempFile -ErrorAction SilentlyContinue
git add .
git commit -m "Clean up temporary files"

Write-Host "`nDone! Created $totalCommits commits between $($startDate.ToString('yyyy-MM-dd')) and $($endDate.ToString('yyyy-MM-dd'))"

