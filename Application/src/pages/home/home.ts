import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import * as jsmpeg from 'jsmpeg';
// import WebSocket from 'ws';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

  constructor(public navCtrl: NavController) {

  }

  ngAfterViewInit() {
    var canvas = <HTMLCanvasElement>document.getElementById('videoCanvas');
    let ctx: CanvasRenderingContext2D = canvas.getContext('2d');
    ctx.fillStyle = '#444';
    ctx.fillText('Loading...', canvas.width/2-30, canvas.height/3);
    var client = new WebSocket( 'ws://68.230.95.141:8084/' );
    var player = new jsmpeg(client, {canvas:canvas});
  }
}
