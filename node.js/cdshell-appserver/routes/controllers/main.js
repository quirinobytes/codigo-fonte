exports.landingPage = (req, res, next) => {
  console.log('Chuguei na landingpage')
  var responseText = 'Hello World!'
  responseText += 'Requested at: ' + req.requestTime + ''
  res.send(responseText)
}
