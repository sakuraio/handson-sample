/*
このプログラムはsakura.ioとTwilioとのコラボハンズオンにおいて、Twilio Functionsと連携させるためのものです。
ivrプログラムより本プログラムを実行することで、sakura.ioで生成したIncoming WebhookのURL（SAKURA_URL）に対して指定したJSONデータを送信します。

本プログラムには以下のパッケージが必要です。Ver.は検証時のものを記載しています。
got : 6.7.1

パラメータは以下のように指定します。
PATH : /turn
ACCESS CONTROL ： チェックなし
EVENT ： 指定なし
*/
exports.handler = function(context, event, callback) {
    // switchパラメータで、エアコンのOnとOffを制御　Control on / off of air conditioner with switch parameter
    const sw = event.switch || 'off';
    const value = ( sw === 'on' ? 1 : 0 );
  
    // 返送するJSONデータの指定（ヘッダおよびMODULE_IDを含むボディ）　Specify JSON data to send back
    const got = require('got');
    const headers = JSON.stringify({
      "Content-Type": "application/json",
      "Accept": "application/json"
    });
    const body = JSON.stringify({
      "type": "channels",
      "module": context.MODULE_ID,
      "payload": {
        "channels": [{
          "channel": 0,
          "type": "i",
          "value": value
        }]
      }
    });
  
    // 送信先URLの指定（SAKURA_URL）　Specify the destination URL
    got(context.SAKURA_URL, {
      json: true,
      method: 'POST',
      headers: headers,
      body: body
    })
    // 成功した場合の挙動の指定　Designation of successful behavior
    .then(response => {
      console.log(response);
      callback(null, 'OK');
    })
    // 失敗した場合の挙動の指定　Designation of behavior in case of failure
    .catch(error => {
      console.log(error);
      callback(error);
    });
  };