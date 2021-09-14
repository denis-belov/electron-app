const path = require('path');
const child_process = require('child_process');
const chokidar = require('chokidar');

const
	{
		app,
		BrowserWindow,
		// globalShortcut,
	} = require('electron');



const PATH_ADDONS_NODE_API_TEST_SRC = path.join(__dirname, 'addons/test-cpp/src');



let window = null;



const createWindow = () =>
{
	window = new BrowserWindow
	(
		{
			width: 800,
			height: 600,

			webPreferences:
			{
				preload: path.join(__dirname, 'preload.js'),

				// Unify nodejs and chromium memory spaces.
				contextIsolation: false,
			},
		},
	);

	// window.setFullScreen(true);
	window.toggleDevTools();

	// window.loadFile(path.join(__dirname, 'frontend/build/index.html'));

	window.loadURL('http://localhost:8080');
};

app
	.whenReady()
	.then
	(
		() =>
		{
			createWindow();

			const frontend_process =
				child_process
					.spawn
					(`cd ${ __dirname } && npm run start:frontend`, { shell: true });

			process.on
			(
				'exit',

				() =>
				{
					// Killing all node processes on linux.
					// Find a better cross-OS way to kill frontend process.
					child_process.execSync('killall -9 node');
				},
			);

			frontend_process.stdout.on
			(
				'data',

				() =>
				{
					window.reload();
				},
			);

			// Watch non-frontend modules.
			// Frontend is watched by webpack.
			chokidar
				.watch
				(
					[
						PATH_ADDONS_NODE_API_TEST_SRC,
					],
				)
				.on
				(
					'change',

					(evt) =>
					{
						if (evt.includes(PATH_ADDONS_NODE_API_TEST_SRC))
						{
							console.log
							(
								child_process
									.execSync
									(`cd ${ __dirname } && npm run build:addon:test-cpp`, { encoding: 'utf8' }),
							);

							window.close();

							createWindow();
						}
					},
				);
		},
	);
