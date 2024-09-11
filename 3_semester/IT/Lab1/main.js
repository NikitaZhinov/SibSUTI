const http = require('http');
const fs = require('fs');

const hostname = '127.0.0.1';
const port = 5500;

const server = http.createServer((req, res) => {
  fs.readFile('html/index.html', (err, data) => {
    if (err) {
      res.writeHead(500);
      res.end('Error! File index.html was not loaded!\n');
    } else {
      res.statusCode = 200;
      res.setHeader('Content-Type', 'text/html');
      res.end(data);
    }
  });
})

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`)
})
