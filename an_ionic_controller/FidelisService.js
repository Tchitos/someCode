"use strict";

angular.module('FidApp').factory('FidelisService', function (WalletekApi, localStorageService, $q, $resource, $http) {

  var serviceUri = WalletekApi.getServer() + "/service/fidelis";
  var Fidelis = $resource(serviceUri, {}, {
    save: {
      method: "POST",
      url: serviceUri + "/save"
    },
    update: {
      method: "POST",
      url: serviceUri + "/update"
    },
    find: {
      method: "GET",
      url: serviceUri + "/:id"
    },
    query: {
      method: "GET",
      url: serviceUri + "/owner/:id",
      isArray: true,
      interceptor: {
        response: function (data) {
          //data.resource = data.resource.filter(self.isValid);
          angular.forEach(data.resource, function(item) {
            item = new Fidelis(item);
          });
          return data.resource;
        }
      }
    }
  });

  var self = this;

  this.saveCard = function (card) {
    return Fidelis.save(card);
  };

  this.updateCard = function (card) {
    return Fidelis.update(card);
  };

  this.getCardsById = function (id) {
    return Fidelis.find({"id": id}, function (result) {
    });
  };

  this.getCardsByOwner = function (id) {
    return Fidelis.query({"id": id}, function (result) {

    });
  };

  this.isValid = function (card) {
    return card !== null && card.code !== null && card.code.value !== null && card.code.format !== null &&
      card.name !== null && card.code.code !== "" && card.code.format !== "";
  };

  this.shareCard = function(idCard, idUser) {
      return $http.post(serviceUri + "/" + idCard + "/shareTo/" + idUser, {});
  };

  this.unShareCard = function(idCard, idUser) {
      return $http.post(serviceUri + "/" + idCard + "/unShareTo/" + idUser, {});
  };

  this.deleteCard = function(idCard) {
    return $http.delete(serviceUri + "/" + idCard);
  }

  return this;

});
