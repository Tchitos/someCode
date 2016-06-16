module.exports.make = function (mongoose) {

    var bcrypt = require('bcrypt');
    var SALT_WORK_FACTOR = 10;

    var restaurantSchema = mongoose.Schema({
        _email: String,
        _restaurantName: String,
        _password: String,
        _address: String,
        _city: String,
//    _GPSPosition: {type: [Number], default: undefined},
        _nbTable:{type: Number, default: 0},
        _dishes: {type: [{}], default: undefined}

    });


    /* Crypt password */
    restaurantSchema.pre('save', function (next) {
        var user = this;

        if (!user.isModified('_password')) {
            return next();
        }

        bcrypt.genSalt(SALT_WORK_FACTOR, function (err, salt) {
            if (err) {
                return next(err);
            }

            bcrypt.hash(user._password, salt, function (err, hash) {
                if (err) {
                    return next(err);
                }

                user._password = hash;
                next();
            });
        });
    });

    /* COMPARE METHOD */
    restaurantSchema.methods.comparePassword = function (candidatePassword, callback) {
        bcrypt.compare(candidatePassword, this._password, function (err, isMatch) {
            if (err) {
                return callback(err);
            }
            callback(undefined, isMatch);
        });
    };

    return mongoose.model('restaurants', restaurantSchema);
};