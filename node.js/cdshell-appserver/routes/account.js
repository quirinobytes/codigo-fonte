require('rootpath')()
const express = require("express");
const accountController = require("routes/controllers/account");
const router = express.Router();
// router
//   .route("/login")
//   .get(accountController)
//   //.post(accountController.userLogin);
// router
//   .route("/signup")
//   //.get(accountController.signupPage)
//   //.post(accountController.createUser);
// router
  //.route("/logout")
  //.get(accountController.logout);
module.exports = router;