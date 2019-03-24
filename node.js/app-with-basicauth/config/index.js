var config = {
  production: {
    mongo : {
      user: 'root',
      pw: 'senha'
    }
  },
  default: {
    mongo : {
      user: 'admin',
      senha: 'senha'
    }
  }
}

exports.get = function get(env) {
  return config[env] || config.default
}
