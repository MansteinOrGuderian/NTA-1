# NTA_lab1
Docker instruction
- download docker from remote: `docker pull mansteinorguderian/ntafirst:latest`
- run docker from remote: `docker run --rm -it mansteinorguderian/ntafirst:latest`
- build from git repository: `docker build -t 'mansteinorguderian/ntafirst' .`
- run cli: `docker run --rm -it 'mansteinorguderian/ntafirst'`
- stop container: `docker stop $(docker ps | grep "mansteinorguderian/ntafirst" | cut -d " " -f1)`
- remove image: `docker image rm 'mansteinorguderian/ntafirst`
