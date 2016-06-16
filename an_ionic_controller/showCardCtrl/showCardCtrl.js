angular.module('FidApp').controller('showCardCtrl', function ($scope, $state, $http, WalletekApi, $stateParams, UserService, $ionicModal, FidelisService) {

  // INIT
  $scope.card = UserService.searchCardById($stateParams.id);
  if ($scope.card == null)
    $state.go('app.home');

  if (window.cordova) {
    window.brightness = cordova.require("cordova.plugin.Brightness.Brightness");
    window.brightness.getBrightness(function (param) {
      $scope.oldBrightness = param;
    }, function (param) {
      $scope.oldBrightness = -1.0;
    });
  }

  if (FidelisService.isValid($scope.card)) {
    if ($scope.card.code.format === "EAN13") {
      $scope.card.code.format = "EAN";
    }
    //console.log(modal.$el);
  }

  $scope.info = {
    desc: $scope.card.description
  };

  // FUNCTION
  $scope.updateInfo = function (infoForm) {
    if (infoForm.$valid) {
      $scope.card.description = $scope.info.desc;
      FidelisService.updateCard($scope.card);
    }
  };

  $scope.deleteCard = function () {
    UserService.deleteCard($scope.card.id);
    var status = FidelisService.deleteCard($scope.card.id);
    $state.go('app.home');
  };

  $scope.goshare = function () {
    $state.go('app.shareCard', { id: $scope.card.id });
  };

  $scope.IsOwner = function() {
    return (UserService.about().id == $scope.card.owner);
  };


  // ======== MODAL ====================
  var modal = $ionicModal.fromTemplateUrl('image-modal.html', {
    scope: $scope,
    animation: 'slide-in-up'
  }).then(function(modal) {
    $scope.modal = modal;
  });

  $scope.openModal = function() {
    if (window.cordova) {
      window.brightness.getBrightness(function (param) {
        $scope.oldBrightness = param;
      }, function (param) {
        $scope.oldBrightness = -1.0;
      });
      window.brightness.setBrightness(1);
    }
    $scope.modal.show();
  };

  $scope.closeModal = function() {
    if (window.cordova) {
      window.brightness.setBrightness($scope.oldBrightness);
    }
    $scope.modal.hide();
  };

  //Cleanup the modal when we're done with it!
  $scope.$on('$destroy', function() {
    $scope.modal.remove();
  });
  // Execute action on hide modal
  $scope.$on('modal.hide', function() {
  });
  // Execute action on remove modal
  $scope.$on('modal.removed', function() {
    // Execute action
  });
  $scope.$on('modal.shown', function() {
    $("#barcode").JsBarcode($scope.card.code.code, {format: $scope.card.code.format, displayValue: true, fontSize: 20});
    // Modal is shown
  });
});
