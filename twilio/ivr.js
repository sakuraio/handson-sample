/*
このプログラムはsakura.ioとTwilioとのコラボハンズオンにおいて、Twilio Functionsと連携させるためのものです。
outboundcallプログラムより本プログラムを実行することで、自動音声応答装置（IVR）として音声案内およびプッシュホンによる操作プログラム（turn-on&turn-off）を実行させます。
パラメータは以下のように指定します。
PATH : /ivr
ACCESS CONTROL ： チェックあり
EVENT ： 指定なし
*/

exports.handler = function(context, event, callback) {
    let twiml = new Twilio.twiml.VoiceResponse()
    // 音声の指定（声、言語）
    let voiceParam = {}
    voiceParam.voice = 'alice'
    voiceParam.language = 'ja-JP'
    // ユーザによるキー入力の条件指定（桁数、タイムアウト値）
    let gatherParam = {}
    gatherParam.numDigits = 1
    gatherParam.timeout = 10
    // キー入力による分岐（turn-on&turn-off）へのリダイレクトおよび初回の呼び出し内容（default）の指定
    switch (event.Digits) {
      case '1':
        twiml.say(voiceParam, 'エアコンをつけます')
        twiml.redirect('https://'+context.DOMAIN_NAME+'/turn-on')
        break
      case '0':
        twiml.say(voiceParam, 'エアコンを消します')
        twiml.redirect('https://'+context.DOMAIN_NAME+'/turn-off')
        break
      default:
        twiml.pause({"length": 2})
        twiml.gather(gatherParam)
          .say(voiceParam, '室温が上昇しています。エアコンをつける場合は、１を押してください。エアコンを停止する場合は０を押してください。')
    }
    callback(null, twiml)
  }