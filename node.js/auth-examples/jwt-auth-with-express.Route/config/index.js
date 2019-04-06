require('rootpath')()
var fs = require('fs')
var key = fs.readFileSync('config/keys/key.pem').toString()
var cert = fs.readFileSync('config/keys/cert.pem').toString()

var config = {
  production: {
    mongo: { user: { username: 'root', password: '****' } },
    server: { http_port: 80, https_port: 3003 },
    certificate_options: { key: key, cert: cert }
  },
  default: {
    mongo: { user: { username: 'root', password: '****' } },
    server: { http_port: 80, https_port: 443 },
    certificate_options: { key: key, cert: cert },
    users: [
      {
        id: 1,
        username: 'admin',
        password: '123',
        role: 'admin'
      },
      {
        id: 2,
        username: 'quirinobytes',
        password: 'xman',
        role: 'user'
      },
      {
        id: 3,
        username: 'felipe',
        password: 'bro123',
        role: 'user'
      }
    ]
  }
}

exports.get = function get (env) {
  return config[env] || config.default
}
