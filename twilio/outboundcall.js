/*
このプログラムはsakura.ioとTwilioとのコラボハンズオンにおいて、Twilio Functionsと連携させるためのものです。
こちらで生成されたURLをsakura.ioのOutgoing Webhookで指定することにより、sakura.ioで取得されたセンサデータはJSONデータとして本プログラムで処理されます。

本プログラムの動作に必要なパッケージはありません。

パラメータは以下のように指定します。
PATH : /outboundcall
ACCESS CONTROL ： チェックなし
EVENT ： 指定なし
*/
exports.handler = function(context, event, callback) {
  console.log(event);

  // モジュールからのメッセージの場合のみ処理を行う(切断・接続メッセージなどは無視) Determining the message type
  var messageType = event.type;
  if (messageType !== "channels") {
      console.log("messageType is not channels");
      callback(null, 'ignored messageType');
      return;
  }

  // 受信したJSONデータに含まれるモジュールIDと、Functionsで指定した環境変数（MODULE_ID）を照合 Verification of module ID
  var moduleId = event.module || '';

  // 一致していた場合のみ、環境変数（TO_NUMBER&FROM_NUMBER）で指定した番号に架電 If the ID matches, call to the specified phone number
  if (moduleId === context.MODULE_ID) {
    var client = context.getTwilioClient();
    console.log("call /ivr");
    client.calls.create({
      // 別途作成するプログラム（ivr）を実行 Execute separately created program
      url: 'https://'+context.DOMAIN_NAME+'/ivr',
      to: context.TO_NUMBER,
      from: context.FROM_NUMBER,
    })
    .then((call) => callback(null, call.sid))
    .catch((error)=> callback(error));
  } else {
    callback(null, 'moduleId was unmatch');
  }
};