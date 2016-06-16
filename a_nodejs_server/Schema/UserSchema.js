module.exports.make =  function (mongoose)  {

    var bcrypt = require('bcrypt');
    var SALT_WORK_FACTOR = 10;

    var userSchema = mongoose.Schema({
        _email: {type: String, unique: true},
        _password: String,
        _firstname: String,
        _lastname: String,
        _coupon: {type: [String], default: undefined},
        _friends: {type: [String], default: undefined}
    });

    /* Crypt password */
    userSchema.pre('save', function (next) {
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
    userSchema.methods.comparePassword = function (candidatePassword, callback) {
        bcrypt.compare(candidatePassword, this._password, function (err, isMatch) {
            if (err) {
                return callback(err);
            }
            callback(undefined, isMatch);
        });
    };

    return mongoose.model('users', userSchema);
};
