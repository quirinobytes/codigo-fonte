var express = require('express');
var https = require('https');
var fs = require('fs');
var routes = require('./routes/index');
var path = require('path');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
passport = require('passport');
FacebookStrategy = require('passport-facebook').Strategy;





var session = require('express-session');

var routes = require('./routes/index');


var app = express()
// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use('/', routes);

app.use(session({
  secret: 'https://developers.facebook.com/apps/396146767609044/settings/basic/',
  resave: true,
  saveUninitialized: true
}));
app.use(passport.initialize());
app.use(passport.session());

passport.serializeUser(function(user, done) {
  done(null, user);
});

passport.deserializeUser(function(obj, done) {
  done(null, obj);
});

// Use the FacebookStrategy within Passport.
//   Strategies in Passport require a `verify` function, which accept
//   credentials (in this case, an accessToken, refreshToken, and Facebook
//   profile), and invoke a callback with a user object.
passport.use(new FacebookStrategy({
    clientID: '396146767609044',
    clientSecret: '7bb9b08d82349e6ceaf22a98f827f3be',
    callbackURL: "https://servidorpush.superati.com.br:3000/auth/facebook/callback"
  },
  function(accessToken, refreshToken, profile, done) {
    // asynchronous verification, for effect...
    process.nextTick(function () {
      
      // To keep the example simple, the user's Facebook profile is returned to
      // represent the logged-in user.  In a typical application, you would want
      // to associate the Facebook account with a user record in your database,
      // and return that user instead.
      return done(null, profile);
    });
  }
));






module.exports = app;