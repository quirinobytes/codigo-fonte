require('rootpath')()
var fs = require('fs')
var key = fs.readFileSync('config/keys/key.pem').toString()
var cert = fs.readFileSync('config/keys/cert.pem').toString()

var config = {
  production: {
    mongo: { user: { username: "root", password: "****" } },
    server: { http_port: 80, https_port: 443 }
  },
  default: {
    mongo: { user: { username: "root", password: "****" } },
    server: { http_port: 80, https_port: 443 },
    certificate_options: { key: key, cert: cert }
  }
}

exports.get = function get (env) {
  return config[env] || config.default
}
