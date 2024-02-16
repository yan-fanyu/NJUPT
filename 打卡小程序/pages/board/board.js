// pages/board/board.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    user_id:'',
    clockIns:[]
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
     this.findUserId();
  },

  sortCountByDesc(){
    const that = this;
    if (!that.data.user_id) {
      console.log('用户ID未设置，无法排序');
      return;
    }
    // console.log("这是sortCount的函数："+that.data.user_id);
    // console.log("这是sortCount的函数："+this.data.user_id);
    wx.cloud.callFunction({
      name: 'getClockSort',
      data: {
        user_id1: that.data.user_id // 这里应该是已经获取到的用户ID
      },
      success: res => {
        if (res.result.code === 200) {
          that.setData({
            clockIns: res.result.data
          });
          console.log('调用数据成功：'+that.data.clockIns);
        } else {
          console.error(res.result.message);
        }
      },
      fail: err => {
        console.error(err);
      }
    });
  },

  findUserId(){
    const that = this;
    wx.cloud.callFunction({
      name:'getOpenId'
    })
    .then(res => {
      console.log('我在findUserId里的openid',res.result.openid)
      that.setData({
        user_id: res.result.openid
      })
      console.log("this.data.user_id:"+that.data.user_id);
      that.sortCountByDesc(); // 现在调用 sortCountByDesc

    })
    .catch(res=>{
      console.log('失败',res)
    })
  },
  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow() {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload() {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom() {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage() {

  }
})