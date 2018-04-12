


/*
Load all models here
*/
let express = require('express'),
	bodyParser = require('body-parser'),
	fs = require('fs'),
	morgan = require('morgan'),
	cookieParser = require('cookie-parser'),
	cors = require('cors'),
	app = express(),
	path = require('path'),
	router = express.Router(),
	session = require('express-session');




  // Middleware.
app.use(require('morgan')('combined'));

app.use(require('compression')());

app.use(express.static('./app/static'));

//Load cookie parser
app.use(cookieParser());

//parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: true }));

//parse application/json
app.use(bodyParser.json())

//server side session
app.use(session({
	secret: 'royalrenderapp',
	resave: false,
  saveUninitialized: true
}))

//Load HTTP access control(CROS)
app.use(cors());



/*************************************************
Reads controller directory and requires all files
**************************************************/
fs.readdirSync(__dirname+"/controllers").forEach(function(filename) {
	if(filename.indexOf('.js')) {
		require("./controllers/"+filename)(router);
	}
});
/**********************************************************
Reads controller directory and requires all files ends here
***********************************************************/


//uses router module
app.use("/api",router);

//client routing, enables to refresh ui page
app.get('*', (req, res) => {
  res.sendFile(path.resolve(__dirname, '..', 'static', 'index.html'));
});

//server connects to localhost at port 3000
app.listen(3000, function () {
  console.log("Server connect at port:3000")
});
