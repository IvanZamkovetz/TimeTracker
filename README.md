# TimeTracker
C++ server and C# client for tracking developer workflow

Application intended for tracking developer workflow in background mode
and send information about it through named pipe to other C# application client

Functionality
1. Tracks mouse moving and hits of keyboard
2. Replies to C# client with hashed information about elapsed time, working project and task

Features
1. boost smart pointers and threads, STL vectors
2. single responsibility pattern
3. background mode (service)
