var gulp          = require('gulp');
var gls           = require('gulp-live-server');
var sass          = require('gulp-sass');
var IS_PRODUCTION = process.env.NODE_ENV === 'production';
var webpack       = require('gulp-webpack');

var paths = {
  main_css : [ 'app/client/stylesheets/main.scss' ],
  css      : [ 'app/client/stylesheets/**/*.scss' ],
  main_js  : [ 'app/client/app.js' ],
  js       : [ 'app/client/**/*.js*' ],
};

gulp.task('css', function() {
  return gulp .src(paths.main_css)
              .pipe(
                sass({
                  outputStyle: IS_PRODUCTION ? 'compressed' : 'nested'
                }).on('error', sass.logError)
              )
              .pipe(gulp.dest('app/static/css/'));
});

gulp.task('js', function() {
  return gulp.src(paths.main_js)
  .pipe(webpack( require('./webpack.config.js') ))
  .pipe(gulp.dest('app/static/js'));
});

gulp.task('serve', [ 'css', 'js' ], function () {
  // Generic watch tasks for SASS and webpack
  gulp.watch(paths.css, [ 'css' ]);
  gulp.watch(paths.js,  [ 'js'  ]);

  // Start the app server.
  var server = gls('app/server/index.js', { stdio : 'inherit' });
  server.start();

  // Reload server when backend files change.
  gulp.watch([ 'app/server/*/*.js' ], function() {
    server.start.bind(server)();
  });

  // Notify server when frontend files change.
  gulp.watch([ 'app/static/**/*.{css,js,html}' ], function(file) {
    server.notify(file);
  });
});

gulp.task('default', [ 'css', 'js' ]);
