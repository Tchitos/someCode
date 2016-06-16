var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');

try {
    mongoose.connect('mongodb://localhost/test');
} catch (e) {
}

var RestaurantModel = require('../Schema/RestaurantSchema').make(mongoose);

/* GET restaurants list. */
router.get('/', function(req, res) {
   RestaurantModel.find({}, function(err, dataFound) {
       if (err) {
           console.log(err);
           res.status(500).send();
       } else {
           res.send(dataFound);
       }
   });
});

/* GET restaurant id*/
router.get('/restaurant', function(req, res) {
    if (req.session.user){
        var restaurant = req.session.user;
        res.send(restaurant);
    }
    res.send(restaurant);
});

/* POST register a restaurant */
router.post('/register', function(req, res) {
    var newRestaurant = new RestaurantModel();

    newRestaurant._restaurantName = req.body.restaurantName;
    newRestaurant._password = req.body.password;
    newRestaurant._city = req.body.city;
    newRestaurant._address = req.body.address;

    newRestaurant.save(function (err, savedObject) {
        if (err) {
            console.log(err);
            res.status(500).send();
        } else {
            res.send(savedObject);
        }
    });
});

/* POST login */
router.post('/login', function (req, res) {
    var restaurantName = req.body.restaurantName;
    var password = req.body.password;

    RestaurantModel.findOne({_restaurantName : restaurantName}, function (err, foundUser) {
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


/* PUT modify a restaurant*/
router.put('/', function(req, res) {
    var id = req.body.id;

    RestaurantModel.findOne({_id : id}, function (err, objectFound) {
        if (err) {
            console.log(err);
            res.status(500).send();
        } else {
            if (!objectFound) {
                res.status(404).send();
            } else {

                if (req.body.tables){
                    objectFound._nbTable = req.body.tables;
                }
                if (req.body.dishes){
                    objectFound._dishes = req.body.dishes;
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

/* DELETE a restaurant */
router.delete('/:id', function (req, res) {
    var id = req.params.id;

    RestaurantModel.findOneAndRemove({_id : id}, function (err) {
        if (err) {
            console.log(err);
            res.status(500).send();
        } else {
            res.status(200).send();
        }
    });
});

/*POST dishes*/

router.post('/dishes', function (req, res) {
    var restaurant = req.session.restaurant;
    var dishes = req.params.dishes;

    RestaurantModel.findOne({_restaurantName: restaurant._restaurantName}, function (err, restaurantFound) {
        if (err) {
            console.log(err);
            return res.status(500).send();
        }
        restaurantFound._dishes.push(dishes);
        restaurantFound.save(function(err, restaurantSaved){
           if (err) {
               console.log(err);
               return res.status(500).send();
           }
            return res.status(200).send(restaurantSaved);
        });
    });
});

module.exports = router;
