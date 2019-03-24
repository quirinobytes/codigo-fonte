exports.loginPage = (req, res, next) => {
  console.log('passei aqui LOGIN PAGE')
  var responseText = 'Hello World!'
  responseText += 'Requested at: ' + req.requestTime + ''
  res.send(responseText)
}
