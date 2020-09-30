const express = require('express');
const exphbs = require('express-handlebars');
const nodemailer = require('nodemailer');
const cookieParser = require('cookie-parser');
const bodyParser = require('body-parser');
const crypto = require('crypto');
const MongoClient = require('mongodb').MongoClient;

const uri = "mongodb+srv://Aaron:FWzrE3LkyShVgcwG@users.rutzq.mongodb.net/Users?retryWrites=true&w=majority";
const app = express();
var tokens = new Map();
app.use(cookieParser());
app.use(bodyParser.urlencoded({extended: true}));
app.use(express.static('public'));
app.engine('hbs', exphbs({extname: '.hbs'}));
app.set('view engine', 'hbs');

//helper functions
function hashPassword(password) {
    const sha256 = crypto.createHash('sha256');
    return sha256.update(password).digest('base64');
}

function getToken() {
    return crypto.randomBytes(20).toString('hex');
}

//connection to db
const client = new MongoClient(uri, { useUnifiedTopology: true }, { useNewUrlParser: true });
client.connect(err => {
  const collection = client.db("Users").collection("Users");
  if (err) throw err;

  //adding new user to db
  app.post('/create_user', function(req, res) {
    const hashedPassword = hashPassword(req.body.password);
    const user = {
        username: req.body.username,
        password: hashedPassword,
        email: req.body.email,
        token: getToken(),
        confirmed: false
    }
    collection.insertOne(user, err => {
        if (err) throw err;
    });
    
    //sending an email to new user informing them to await confirmation
    const smtpTrans = nodemailer.createTransport({
        host: 'smtp.gmail.com',
        port: 465,
        secure: true,
        auth: {
            user: 'ariecktutor@gmail.com',
            pass: 'Ajrd0g123456'
        }
    })

    var message = {
        from: 'Door Opener',
        to: req.body.email,
        subject: 'Door Opener - Awaiting Confirmation',
        text: 'Hello ' + req.body.username + ', thank you for registering with us. If your account is confirmed, you will receive' +
        ' another message informing you that you may sign in and open your door.'
    }

    smtpTrans.sendMail(message, function(error, response) {
        if (error) throw error;
    })
    res.redirect('/');
  })

    //handling login logic
    app.post('/login', function(req, res) {
        const hashedPassword = hashPassword(req.body.password);
        //finding user in db
        collection.find({'username' : req.body.username, 'password' : hashedPassword}).toArray(function (err, result) {
            if (err) throw err;
            if (result[0] == undefined) {
                res.render('home', {
                    message: 'Invalid username or password',
                    messageClass: 'alert-danger'
                });
            } 
            //sending admin to admin page
            else if(result[0].username === 'admin') {
                res.redirect('/admin');
            } 
            //checking if user is confirmed by admin
            else if(result[0].confirmed != true) {
                res.render('home', {
                    message: 'Account must be confirmed',
                    messageClass: 'alert-danger'
                });
            }
            //storing a token in the server and sending it to the client for authentication
            else {
                res.cookie('Token', result[0].token, {maxAge: 60000});
                res.redirect('/success');
            }
         })
    })
    
    //checks if client has an auth token before successfully logging in
    app.get('/success', function(req,res) {
        collection.find({}, { projection: { token: 1 } }).toArray(function(err, result) {
            var sessionCookie = req.cookies['Token']
            for (var i = 0; i < result.length; i++) {
                if (sessionCookie == result[i].token && sessionCookie != null) {
                    res.sendFile('public/success.html', {root : __dirname})
                    return;
                }
            }
            res.redirect('/rejected');
        })
    })

    //admin login
    app.get('/admin', function(req, res) {
        collection.find({}).toArray(function (err, result) {
            if (result == undefined) {
                throw new Error('Database is empty!');
            } 
            res.render('admin', {
                usernames: result
            })
        })
    })

    //confirming a user by admin
    app.post('/confirm', function(req, res){
        collection.updateOne({username: req.body.username}, { $set: {confirmed: true}}, function(err, res) {
            if (err) throw err;
        })

        collection.find({username : req.body.username}).toArray(function (err, result) {
            //sending an email to new user informing them they have been confirmed
            const smtpTrans = nodemailer.createTransport({
                host: 'smtp.gmail.com',
                port: 465,
                secure: true,
                auth: {
                    user: 'ariecktutor@gmail.com',
                    pass: 'Ajrd0g123456'
                }
            })

            var message = {
                from: 'Door Opener',
                to: result[0].email,
                subject: 'Door Opener - Confirmed!',
                text: 'Hello ' + req.body.username + ', your account has been confirmed! You may now log in and open your door.'
            }

            smtpTrans.sendMail(message, function(error, response) {
                if (error) throw error;
            })
        })
        res.redirect('/admin');
    })
});

app.get('/', function(req, res) {
    res.render('home');
});

app.get('/rejected', function(req,res) {
    res.render('rejected');
})

app.get('/try_again', function(req, res) {
    res.redirect('/');
})

app.get('/logout', function(req, res) {
    res.clearCookie('Token');
    res.redirect('/');
})

app.get('/create', function(req, res) {
    res.render('create');
})

app.listen(8080);