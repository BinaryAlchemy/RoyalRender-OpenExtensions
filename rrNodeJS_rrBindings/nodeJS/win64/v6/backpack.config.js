const path = require('path')
module.exports = {
  webpack: (config, options, webpack) => {
      config.entry.main = ['./src/index.ts'],
      config.output.path = path.resolve(__dirname, 'lib'),
      config.output.filename = 'index.js',
  
      config.resolve = {
        extensions: ['.ts', '.js', '.json']
      },
  
      config.module.rules.push({
        test: /\.ts$/,
        loader: 'awesome-typescript-loader'
      }),

      config.module.rules.push({
          test: /\.node$/,
          use: 'node-loader'
      })
  
      return config
    }
  }
  