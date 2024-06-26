# Use the official gcc image from the Docker Hub
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY Header.h /usr/src/app/
COPY main.cpp /usr/src/app/
COPY Functions.cpp /usr/src/app/

# Compile the C++ program
RUN g++ -o myapp main.cpp Functions.cpp

# Command to run the executable
CMD ["./myapp"]