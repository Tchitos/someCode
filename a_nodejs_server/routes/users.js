var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
try {
    mongoose.connect('mongodb://localhost/test');
} catch (e) {
}
var UserModel = require('../Schema/UserSchema').make(mongoose);


/* GET users list. */
router.get('/', function(req, res) {
    UserModel.find({}, function (err, dataFound) {
        if (err) {
            console.log(err);
            res.status(500).send();
        } else {
            res.send(dataFound);
        }
    });
});

/* GET a specific user */
router.get('/user/:username', function(req, res) {
    var username = req.params.username;
    var responseObject = {username: username};

    res.send(responseObject);
});


/* POST a new user */
router.post('/register', function(req, res) {

    var newUser = new UserModel();
    newUser._email = req.body.email;
    newUser._password = req.body.password;
    newUser._firstname = req.body.firstname;
    newUser._lastname = req.body.lastname;

    newUser.save(function (err, savedUser) {
        if (err) {
            console.log(err);
            return res.status(500).send();
        }
        return res.status(200).send(savedUser);
    });
});

/* POST login */
router.post('/login', function (req, res) {
    var email = req.body.email;
    var password = req.body.password;

    console.log("LOGIN : " + email + password);
    UserModel.findOne({_email : email}, function (err, foundUser) {
        if (err) {
            console.log(err);
            return res.status(500).send();
        }

        if (!foundUser) {
            return res.status(404).send();
        }

        foundUser.comparePassword(password, function (err, isMatch) {
            if (isMatch && isMatch == true) {
                req.session.user = foundUser;
                return res.status(200).send(foundUser);
            } else {
                return res.status(401).send();
            }
        });
    });
});

/* GET logout */
router.get('/logout', function (req, res) {
    req.session.destroy();
    res.status(200).send();
});

/* PUT modify a user */
router.put('/:id', function (req, res) {
    var id = req.params.id;

    UserModel.findOne({id : id}, function (err, objectFound) {
        if (err) {
            console.log(err);
            res.status(500).send();
        } else {
            if (!objectFound) {
                res.status(404).send();
            } else {
                if (res.body.username) {
                    objectFound._username = res.body.username;
                }
                if (res.body.password) {
                    objectFound._password = res.body.password;
                }

                objectFound.save(function (err, objectUpdated) {
                    if (err) {
                        console.log(err);
                        res.status(500).send();
                    } else {
                        res.send(objectUpdated);
                    }
                });
            }
        }
    });
});

/* DELETE user*/
router.delete('/:id', function (req, res) {
    id = req.params.id;

    UserModel.findOneAndRemove({_id : id}, function (err) {
        if (err) {
            console.log(err);
            return res.status(500).send();
        } else {
            return res.status(200).send();
        }
    });
});

/* ADD a coupon*/
router.post('/addcoupon', function (req, res) {
    UserModel.findOne({id: req.body.id}, function (err, userFound) {
        if (err) {
            console.log(err);
            return res.status(500).send();
        }
        userFound._coupon.push(req.body.coupon);
        userFound.save(function (err, userSaved) {
            if (err) {
                console.log(err);
                return res.status(500).send();
            }
            return res.status(200).send(userSaved);
        });
    });
});

router.get('/coupons/:id', function (req, res) {
    var userID = req.params.id;
    var coupons;

    UserModel.findOne({_id : userID}, function (err, userFound) {
        if (err) {
            console.log(err);
            return res.status(500).send();
        }
        coupons = userFound._coupon;
        return res.status(200).send(coupons);
    })
});

module.exports = router;
